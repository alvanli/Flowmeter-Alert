#include "C:/DATA/Git/Flowmeter-Alert/Code/library/lcd.h"

int randVal = 0;

void setup() {
  randomSeed(analogRead(0)); // assuming pin 0 isn't used
  lcdInit();
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  if (!showFlash && !playing) { // play alarm randomly
    randVal = random(100);
    if (randVal < 2) {
      setWarningString("TOO HIGH");
      forceRefresh();
      playing = true;
      showFlash = true;
    }
  }

  if (!playing && !showFlash && !warning_string.equals("NO WARNING")) { // reset message if needed
    setWarningString("NO WARNING");
    forceRefresh();
  }
  
  showMenuAlarmCheck(0);
}
