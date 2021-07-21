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
    radio.read(&pos, sizeof(pos));    //Reading the data
    if (pos == 1) {
      setWarningString("TOO HIGH");
      forceRefresh();
      playing = true; // Toggle bool to play tone
    } else if (pos == -1) {
      setWarningString("TOO LOW");
      forceRefresh();
      playing = true; // Toggle bool to play tone
    } else if (!pos) {
      setWarningString("GOOD");
      forceRefresh();
      playing = false;
    }
  }
}
