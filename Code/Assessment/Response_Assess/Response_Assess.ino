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

void loop() {
  if (!showFlash && !playing) { // play alarm randomly
    randVal = random(100);
    if (randVal < 2) {
      setWarningString("TOO HIGH");
      forceRefresh();
      playing = true;
      showFlash = true;
      awaitingInput = true;
    }
  }

  if (!playing && !showFlash && !warning_string.equals("NO WARNING")) { // reset if needed
    setWarningString("NO WARNING");
    forceRefresh();
    awaitingInput = false;
  }

  if (Serial.available() > 0) { // output response time
    Serial.println("Response time (ms): " + String(millis() - timeStart));
  }

  if (!awaitingInput) { // update time if not waiting for user input
    timeStart = millis();
  }
  
  showMenuAlarmCheck(0);
}
