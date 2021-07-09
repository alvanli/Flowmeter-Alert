#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN         
const byte address[6] = "00001";

bool curr = false; // false if below threshold, true if above threshold
int threshold = 250;

int photo1 = A0;
int photo2 = A1;

void setup(){
  pinMode(photo1, INPUT);
  pinMode(photo2, INPUT);
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);  
  radio.stopListening(); 
}

void loop(){
  //int photoValue1 = analogRead(photo1);
  int photoValue2 = analogRead(photo2);
  //Serial.println("Photo resistor 1: " + String(photoValue1));
  Serial.println("Photo resistor 2: " + String(photoValue2));

  //int val1 = threshold_check(photoValue1);
  int val2 = threshold_check(photoValue2);

  if ( val2 != 0) {
    //radio.write(&val1, sizeof(val1));
    radio.write(&val2, sizeof(val2));
  }
  delay(1000); 
}

// return 1 if reading moved below threshold (from good to bad)
// return 0 if no change
// return -1 if reading moved above threshold (from bad to good)
int threshold_check(int reading) {
  if (curr && (reading > threshold)) {
    return -1; 
  } else if (!curr && (reading < threshold)) {
    return 1;
  }
  return 0;
}
