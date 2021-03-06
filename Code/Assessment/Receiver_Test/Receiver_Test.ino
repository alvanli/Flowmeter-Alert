#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#include "C:/DATA/Git/Flowmeter-Alert/Code/library/pitches.h"

#define CE_PIN   9
#define CSN_PIN 10

const int speaker = A3;
const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN);
char dataReceived[10];
bool newData = false;


int waitTime = 2000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  radio.begin();                  //Starting the Wireless communication
  printf_begin();
  check_radio();
}


void check_radio(){
  radio.printDetails();
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.setDataRate( RF24_250KBPS );
  radio.printDetails();
  delay(waitTime);
}

void check_sound(){
  tone(speaker, NOTE_G4, 100);
  delay(1000);
  noTone(speaker);
}
void loop() {
  check_radio();
  
}
