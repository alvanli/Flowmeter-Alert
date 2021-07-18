#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "C:/Users/brian/Desktop/Flowmeter-Alert/library/detectButton.h"
#include "C:/Users/brian/Desktop/Flowmeter-Alert/library/lcd.h"

int lcdKey = 0;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

bool tooHigh = false;
bool tooLow = false;

void setup() {
  Serial.begin(9600);

  lcdInit();

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

  pinMode(speaker_pin, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();
}

void loop() {
  lcdKey = readLCDButtons();
  showMenuAlarmCheck(lcdKey);

  switch(lcdKey) { // Delete??
    case BTN_SELECT: 
      Serial.println("select");
      break;
    case BTN_UP: 
      Serial.println("up");
      break;
    case BTN_DOWN: 
      Serial.println("down");
      break;
    default: 
      break;
  }

  radioRead();
  
}

void radioRead() {
  if (radio.available()){              //Looking for the data.
    int res1 = 0;
    int res2 = 0; //Saving the incoming data
    radio.read(&res1, sizeof(res1));    //Reading the data
    radio.read(&res2, sizeof(res2)); 
    //Serial.println("res 1: " + String(res1));
    //Serial.println("res 2: " + String(res2));
    getBallLocation(res1, res2);
    Serial.println("Too high?: " + String(tooHigh));
    Serial.println("Too low?: " + String(tooLow));
    if (tooHigh && !tooLow) {
      setWarningString("TOO HIGH");
      playing = true; // Toggle bool to play tone
    } else if (!tooHigh && tooLow) {
      setWarningString("TOO LOW");
      playing = true; // Toggle bool to play tone
    } else if (!tooHigh && !tooLow) {
      setWarningString("GOOD");
    }
    //if (tooHigh && tooLow){
      //Serial.println("ERROR: ball is too high and too low at the same time");
    //}
  }
}

void getBallLocation(int res1, int res2) {
  if (res1 == 1){
    tooHigh = true;
  }
  if (res2 == 1){
    tooLow = true;
  }
  if (res1 == -1){
    tooHigh = false;
  }
  if (res2 == -1){
    tooLow = false;
  }
}
