#include "C:/DATA/Git/Flowmeter-Alert/Code/library/detectButton.h"
#include "C:/DATA/Git/Flowmeter-Alert/Code/library/lcd.h"


int randVal = 0;
bool awaitingInput = false;
unsigned long timeStart = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); // assuming pin 0 isn't used
  lcdInit();
  pinMode(speaker_pin, OUTPUT);
  timeStart = millis();
}

int lcdKey = 0;

void loop() {
  lcdKey = readLCDButtons();
  
  if (!showFlash && !playing && !awaitingInput) { // play alarm randomly
    randVal = random(1000);
    if (randVal < 2) {
      setWarningString("TOO HIGH");
      forceRefresh();
      playing = true;
      showFlash = true;
      awaitingInput = true;
    }
  }

  if (!playing && !showFlash && !warning_string.equals("NO WARNING") && !awaitingInput) { // reset if needed
    setWarningString("NO WARNING");
    forceRefresh();
  }
  Serial.println(lcdKey);
  if (lcdKey == BTN_UP) { // output response time
    //Serial.println("Response time (ms): " + String(millis() - timeStart));
    awaitingInput = false;
  }

  if (!awaitingInput) { // update time if not waiting for user input
    timeStart = millis();
  }
  
  showMenuAlarmCheck(0);
}
