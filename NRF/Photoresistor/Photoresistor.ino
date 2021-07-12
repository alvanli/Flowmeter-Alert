#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";

bool blocked1 = false; // true if above threshold (blocked), false if below (not blocked)
bool blocked2 = false;

int photo1 = A0; // higher resistor
int photo2 = A1; // lower resistor

int laser1 = A3; // with A0 (higher) USED TO BE 6
int laser2 = A4; // with A1 (lower) USED TO BE 5

int threshold1 = 250;
int threshold2 = 250;

void setup(){

  randomSeed(analogRead(0)); // CHANGE IF USING PIN 0
  
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

  analogWrite(laser1, 255);
  analogWrite(laser2, 255);
}

void loop(){
  int photoValue1 = analogRead(photo1);
  int photoValue2 = analogRead(photo2);
  Serial.println("Photo resistor 1: " + String(photoValue1));
  Serial.println("Photo resistor 2: " + String(photoValue2));

  int val1 = threshold_check(photoValue1, blocked1, threshold1);
  int val2 = threshold_check(photoValue2, blocked2, threshold2);
  if (val1 == 1){
    blocked1 = true;
  }
  if (val1 == -1){
    blocked1 = false;
  }
  if (val2 == 1){
    blocked2 = true;
  }
  if (val2 == -1){
    blocked2 = false;
  }

  //val1 = photoValue1;
  //val2 = photoValue2;

  if (val1 != 0 || val2 != 0) {
    radio.write(&val1, sizeof(val1));
    radio.write(&val2, sizeof(val2));
  }
  delay(1000); 
}

// return -1 if reading moved below threshold (from bad to good)
// return 0 if no change
// return 1 if reading moved above threshold (from good to bad)
int threshold_check(int reading, bool blocked, int threshold) {
  if (!blocked && (reading > threshold)) {
    return 1; 
  } else if (blocked && (reading < threshold)) {
    return -1;
  }
  return 0;
}

void calib_photores(int photoPin, int cycles, int laser, int t) {
  float sumDim;
  float sumBright;
  // Ambient light
  analogWrite(laser, 0);
  for (int i = 0; i < cycles; i++) {
    sumDim += analogRead(photoPin) / cycles;
    delay(500);
  }
  // Laser light
  analogWrite(laser, 255);
  for (int i = 0; i < cycles; i++) {
    sumBright += analogRead(photoPin) / cycles;
    delay(500);
  }
  analogWrite(laser, 0);
  int threshold = int((sumDim + 4 * sumBright) / 5);
  t ? (threshold2 = threshold) : (threshold1 = threshold);
}

void check_threshold(int photoPin, int laser, int threshold) {
  int reading = 0;
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      reading = analogRead(photoPin);
      if (reading > threshold) {
        Serial.println("Check " + String(i) + ": Good");
      } else {
        Serial.println("Check " + String(i) + ": Bad");
      }
    } else {
      analogWrite(laser, 255);
      reading = analogRead(photoPin);
      if (reading < threshold) {
        Serial.println("Check " + String(i) + ": Good");
      } else {
        Serial.println("Check " + String(i) + ": Bad");
      }
      analogWrite(laser, 0);
    }
    delay(200);
  }
}
