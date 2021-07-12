#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";

bool curr1 = false; // true if below threshold, false if above threshold
bool curr2 = false;

int photo1 = A0;
int photo2 = A1;

int threshold1 = 250;
int threshold2 = 250;

void setup(){
  pinMode(photo1, INPUT);
  pinMode(photo2, INPUT);
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);  
  radio.stopListening(); 
  
  threshold1 = calib_photores(photo1, 10);
  threshold2 = calib_photores(photo2, 10);
  Serial.println("Threshold 1: " + String(threshold1));
  Serial.println("Threshold 2: " + String(threshold2));
}

void loop(){
  int photoValue1 = analogRead(photo1);
  int photoValue2 = analogRead(photo2);
  Serial.println("Photo resistor 1: " + String(photoValue1));
  Serial.println("Photo resistor 2: " + String(photoValue2));

  int val1 = threshold_check(photoValue1, curr1);
  int val2 = threshold_check(photoValue2, curr2);
  if (val1 == 1){
    curr1 = true;
  }
  if (val1 == -1){
    curr1 = false;
  }
  if (val2 == 1){
    curr2 = true;
  }
  if (val2 == -1){
    curr2 = false;
  }

  //val1 = photoValue1;
  //val2 = photoValue2;

  if (val1 != 0 || val2 != 0) {
    radio.write(&val1, sizeof(val1));
    radio.write(&val2, sizeof(val2));
  }
  delay(1000); 
}

// return 1 if reading moved below threshold (from bad to good)
// return 0 if no change
// return -1 if reading moved above threshold (from good to bad)
int threshold_check(int reading, bool curr) {
  if (curr && (reading > threshold)) {
    return -1; 
  } else if (!curr && (reading < threshold)) {
    return 1;
  }
  return 0;
}

int calib_photores(int photoPin, int cycles) {
  float sum;
  for (int i = 0; i < cycles; i++) {
    sum += analogRead(photoPin) / cycles;
  }
  delay(500);
  return int(sum);
}
