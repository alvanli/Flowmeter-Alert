#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";

bool curr1 = false; // true if below threshold, false if above threshold
bool curr2 = false;

int photo1 = A0;
int photo2 = A1;

int laser1 = 6; // with A0
int laser2 = 5; // with A1

int threshold1 = 250;
int threshold2 = 250;

void setup(){
  pinMode(photo1, INPUT);
  pinMode(photo2, INPUT);
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);  
  radio.stopListening(); 
  
  calib_photores(photo1, 10, laser1, 0);
  calib_photores(photo2, 10, laser2, 1);
  Serial.println("Threshold 1: " + String(threshold1));
  Serial.println("Threshold 2: " + String(threshold2));
}

void loop(){
  int photoValue1 = analogRead(photo1);
  int photoValue2 = analogRead(photo2);
  Serial.println("Photo resistor 1: " + String(photoValue1));
  Serial.println("Photo resistor 2: " + String(photoValue2));

  int val1 = threshold_check(photoValue1, curr1, threshold1);
  int val2 = threshold_check(photoValue2, curr2, threshold2);
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
int threshold_check(int reading, bool curr, int threshold) {
  if (curr && (reading > threshold)) {
    return -1; 
  } else if (!curr && (reading < threshold)) {
    return 1;
  }
  return 0;
}

void calib_photores(int photoPin, int cycles, int laser, int t) {
  float sumDim;
  float sumBright;
  // Ambient light
  digitalWrite(laser, LOW);
  for (int i = 0; i < cycles; i++) {
    sumDim += analogRead(photoPin) / cycles;
    delay(100);
  }
  // Laser light
  digitalWrite(laser, HIGH);
  for (int i = 0; i < cycles; i++) {
    sumBright += analogRead(photoPin) / cycles;
    delay(100);
  }
  digitalWrite(laser, LOW);
  int threshold = int((sumDim + sumBright) / 2);
  t ? (threshold2 = threshold) : (threshold1 = threshold);
}
