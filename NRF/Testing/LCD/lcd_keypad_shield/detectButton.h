const int BTN_SELECT = A0;
const int BTN_UP = A1;
const int BTN_DOWN = A2;
const int BTN_THRESHOLD = 1000;
const int BTN_PINS[] = {BTN_SELECT, BTN_UP, BTN_DOWN};

<<<<<<< HEAD
int VRx = A0;
int VRy = A1;
int SW = 8;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

=======
>>>>>>> 0a8c6e4d4db0cc904712fb24cb97a73200462c26
static unsigned long lastInterruptTime = millis();

boolean btnPressed(int readPin){
  //Serial.print(String(readPin) + " ");
  //Serial.println(analogRead(readPin));
<<<<<<< HEAD
  //return analogRead(readPin) > BTN_THRESHOLD;
=======
  return analogRead(readPin) > BTN_THRESHOLD;
>>>>>>> 0a8c6e4d4db0cc904712fb24cb97a73200462c26
}

boolean debounce(boolean prev, int readPin){
  boolean curr = btnPressed(readPin);
  if (prev != curr){
    delay(100);
    curr = btnPressed(readPin);
  }
  return prev;
}

static unsigned long lastRead = millis();

int readLCDButtons() {
  for(int i = 0; i < 4; i++) {
    boolean prev = btnPressed(BTN_PINS[i]);
    boolean curr = debounce(prev, BTN_PINS[i]);
    if (curr && millis() - lastInterruptTime > 100) {
      lastInterruptTime = millis();
      return BTN_PINS[i];
    }
  }
  return 0;
}
