#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "C:/DATA/Git/Flowmeter-Alert/Code/library/transmitter.h"

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";

int photo1 = A0; // higher resistor
int photo2 = A1; // lower resistor

int laser1 = A3; // with A0 (higher) USED TO BE 6
int laser2 = A4; // with A1 (lower) USED TO BE 5

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
  
  threshold1 = calib_photores(photo1, 50, laser1, 0);
  threshold2 = calib_photores(photo2, 50, laser2, 1);
  Serial.println("Threshold 1: " + String(threshold1));
  Serial.println("Threshold 2: " + String(threshold2));

  analogWrite(laser1, 255);
  analogWrite(laser2, 255);
}

void loop(){
  int photoValue1 = analogRead(photo1);
  int photoValue2 = analogRead(photo2);
  
//  Serial.println("Photo resistor 1: " + String(photoValue1));
//  Serial.println("Photo resistor 2: " + String(photoValue2));
  
  int temp = getBallLocation(photoValue1, photoValue2, threshold1, threshold2);
  Serial.println("Position: " + String(temp));
  radio.write(&temp, sizeof(temp));
    
  delay(100); 
}
