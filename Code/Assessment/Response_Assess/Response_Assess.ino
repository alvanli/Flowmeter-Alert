#include "C:/DATA/Git/Flowmeter-Alert/Code/library/detectButton.h"
#include "C:/DATA/Git/Flowmeter-Alert/Code/library/lcd.h"

int randVal = 0;
bool awaitingInput = false;
unsigned long timeStart = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
  randomSeed(analogRead(0)); // assuming pin 0 isn't used
  lcdInit();
  pinMode(speaker_pin, OUTPUT);
  timeStart = millis();
}

int lcdKey = 0;

void loop() {
  lcdKey = readLCDButtons();
  
  if (!showFlash && !playing && !awaitingInput) { // play alarm randomly
    randVal = random(2, 10);
    Serial.println(randVal*3);
    setWarningString("NO WARNING");
    forceRefresh();
    delay(randVal * 1000 * 3);
    timeStart = millis();
    setWarningString("TOO HIGH");
    forceRefresh();
    playing = true;
    showFlash = true;
    awaitingInput = true;
  }

  if (!playing && !showFlash && !warning_string.equals("NO WARNING") && !awaitingInput) { // reset if needed
    setWarningString("NO WARNING");
    forceRefresh();
  }

  if (lcdKey == BTN_SELECT) { // output response time
    Serial.println("Response time (ms): " + String(millis() - timeStart));
    awaitingInput = false;
    setWarningString("NO WARNING");
    forceRefresh();
  }

  
  showMenuAlarmCheck(0);
  delay(1);
}
