const int BTN_SELECT = 42;
const int BTN_UP = 43;
const int BTN_DOWN = 44;
const int BTN_THRESHOLD = 1000;

const int VRx = A0;
const int VRy = A1;
const int SW = 8;

int xPosition = 0;
int yPosition = 0;
int SW_state = 1;

static unsigned long lastInterruptTime = millis();

int readLCDButtons() {
  int lcdKey = 0;
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  if (millis() - lastInterruptTime > 200) {
    if (SW_state == 0) { 
      lcdKey = BTN_SELECT;
      lastInterruptTime = millis();
    } else if(millis() - lastInterruptTime > 500) {
        if (yPosition < 100) {
          lcdKey = BTN_DOWN;
          lastInterruptTime = millis();
        } else if (yPosition > 900) {
          lcdKey = BTN_UP;
          lastInterruptTime = millis();
        } 
    }
    return lcdKey;
  }
  return 0;
}
