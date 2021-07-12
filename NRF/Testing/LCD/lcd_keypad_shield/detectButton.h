const int BTN_SELECT = A0;
const int BTN_UP = A1;
const int BTN_DOWN = A2;
const int BTN_THRESHOLD = 1000;
const int BTN_PINS[] = {BTN_SELECT, BTN_UP, BTN_DOWN};

int VRx = A0;
int VRy = A1;
int SW = 8;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;

static unsigned long lastInterruptTime = millis();

static unsigned long lastRead = millis();

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
          lcdKey = BTN_UP;
          lastInterruptTime = millis();
        } else if (yPosition > 900) {
          lcdKey = BTN_DOWN;
          lastInterruptTime = millis();
        } 
    }
    
    return lcdKey;
  }
  return 0;
}
