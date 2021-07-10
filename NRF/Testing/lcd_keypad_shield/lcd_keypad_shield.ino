#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int lcdKey = 0;

const int btnSelect = A0;
const int btnUp = A1;
const int btnDown = A2;
const int btnBack = A3;
const int btnReset = A4;
const int THRESHOLD = 1000;
const int btnPins[] = {btnSelect, btnUp, btnDown, btnBack, btnReset};

String WARNING = "WORDS OF WARNING";
String ALARM_STR = "Set Alarm";
String THRESHOLD_STR = "Set Threshold";
String LED_STR = "Set LED";
String MENU_ITEMS[] = {ALARM_STR, THRESHOLD_STR, LED_STR};

int readLCDButtons() {
  for(int i = 0; i < 5; i++) {
    boolean prev = analogRead(btnPins[i]) < THRESHOLD;
    boolean curr = debounce(prev, btnPins[i]);
    if (curr) {
      return btnPins[i];
    }
  }
  return 0;
}

boolean debounce(boolean prev, int readPin){
  boolean curr = analogRead(readPin)<THRESHOLD;
  if (prev != curr){
    delay(5);
    curr = analogRead(readPin)<THRESHOLD;
  }
  return curr;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // dimensions of the display
  lcd.setCursor(0, 0); // position of the cursor
  lcd.println(WARNING);

  pinMode(btnSelect, INPUT); 
  pinMode(btnUp, INPUT); 
  pinMode(btnDown, INPUT); 
  pinMode(btnBack, INPUT); 
  pinMode(btnReset, INPUT); 
}

int state = 0; // 0: Warning, 1: Menu, 2: Thres Menu
int menuState = 0; // 0: ALARM_STR, 1: THRESHOLD_STR, 2: LED_STR

void loop() {
  lcdKey = readLCDButtons();
  if (state == 0){ 
    lcd.setCursor(0, 0);
    lcd.println(WARNING);
  }
  else if (state == 1){ 
    lcd.setCursor(0,0);
    lcd.println(MENU_ITEMS[menuState]);  
    int secondState = menuState >= (int)(sizeof(MENU_ITEMS)/sizeof(MENU_ITEMS[0]))-1 ? 0 : menuState+1;
    lcd.setCursor(0,1);
    lcd.println(MENU_ITEMS[menuState]);
    if (lcdKey == btnDown){
      menuState = menuState >= (int)(sizeof(MENU_ITEMS)/sizeof(MENU_ITEMS[0])) ? 0 : menuState + 1;
    }else if (lcdKey == btnUp){
      menuState = menuState == 0 ? 0 : menuState + 1;
    }
  }
  else if (state == 2) { 
    lcd.setCursor(0, 0);
    lcd.println(THRESHOLD_STR);
    lcd.setCursor(0, 1);
    lcd.println(THRESHOLD);
    int threshold = THRESHOLD;
    if (lcdKey == btnDown){
      threshold += 1;
      lcd.setCursor(0, 1);
      lcd.println(threshold);
    }else if (lcdKey == btnUp){
      threshold -= 1;
      lcd.setCursor(0, 1);
      lcd.println(threshold);
    }
  }
  
  switch(lcdKey) {
    case btnSelect: 
      Serial.println("select");
      break;
    case btnUp: 
      Serial.println("up");
      break;
    case btnDown: 
      Serial.println("down");
      break;
    case btnBack: 
      Serial.println("back");
      break;
    case btnReset: 
      Serial.println("reset");
      break;
    default: 
      break;
  }
}
