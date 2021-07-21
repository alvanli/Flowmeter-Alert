#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "C:/Users/brian/Desktop/Flowmeter-Alert/Code/library/detectButton.h"
#include "C:/Users/brian/Desktop/Flowmeter-Alert/Code/library/lcd.h"

int lcdKey = 0;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int pos = 0;

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

    int temp = 0;
    radio.read(&temp, sizeof(temp));    //Reading the data

    if (temp != pos) {
      if (temp == 1) {
        setWarningString("TOO HIGH");
        forceRefresh();
        showFlash = true; // start alarm sequence
      } else if (temp == -1) {
        setWarningString("TOO LOW");
        forceRefresh();
        showFlash = true; // start alarm sequence
      } else if (!temp) {
        setWarningString("GOOD");
        forceRefresh();
        showFlash = false; // start alarm sequence
      }
      pos = temp;
    }
    
  }
}
