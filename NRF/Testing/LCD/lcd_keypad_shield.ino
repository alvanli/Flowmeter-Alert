#include <LiquidCrystal.h>
#include "detectButton.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int lcdKey = 0;

const String WARNING = "WORDS OF WARNING";
const String ALARM_STR = "Alarm";
const String THRESHOLD_STR = "Set Threshold";
const String LED_STR = "LED";
const String RESET_STR = "RESET";
const String MENU_ITEMS[] = {ALARM_STR, THRESHOLD_STR, LED_STR, RESET_STR};
const int MENU_SIZE = 4;
int THRESHOLD = 1000;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // dimensions of the display
  lcd.setCursor(0, 0); // position of the cursor
  lcd.println(WARNING);

  pinMode(BTN_SELECT, INPUT); 
  pinMode(BTN_UP, INPUT); 
  pinMode(BTN_DOWN, INPUT);  
}

int state = 0; // 0: Warning, 1: Menu, 2: Thres Menu
int menuState = 2; // 0: ALARM_STR, 1: THRESHOLD_STR, 2: LED_STR
boolean led_state = true;
boolean alarm_state = true;

String prevMsg1 = "";
String prevMsg2 = "";

void display(String message1, String message2){
  if (!prevMsg1.equals(message1) && !prevMsg2.equals(message2)){
    prevMsg1 = message1;
    prevMsg2 = message2;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(message1);
    lcd.setCursor(0, 1);
    lcd.println(message2);
  }
}

String onOff(boolean isOn){
  return isOn ? "ON" : "OFF";
}

void mainMenuDisplay(int menuState){
  int secondState = menuState >= MENU_SIZE - 1 ? 0 : menuState + 1;
  String firstMessage = MENU_ITEMS[menuState];
  String secondMessage = MENU_ITEMS[secondState];
  firstMessage = ">" + firstMessage;
  if (menuState == 0){
    firstMessage = firstMessage+ ": " + onOff(alarm_state); 
  }else if (menuState == 2){
    firstMessage = firstMessage+ ": " + onOff(led_state);
  }
  if (secondState == 0){
    secondMessage = secondMessage + ": " + onOff(alarm_state); 
  }else if (secondState == 2){
    secondMessage = secondMessage + ": " + onOff(led_state);
  }
  display(firstMessage, secondMessage);
}

void forceRefresh(){
  prevMsg1 = "";
  prevMsg2 = "";
}

void loop() {
  lcdKey = readLCDButtons();
  if (state == 0){ 
    display(WARNING, "");
    if (lcdKey == BTN_SELECT) state = 1;
  }
  else if (state == 1){ 
    mainMenuDisplay(menuState);
    if (lcdKey == BTN_DOWN){
      menuState = menuState >= MENU_SIZE -1 ? 0 : menuState + 1;
    }else if (lcdKey == BTN_UP){
      menuState = menuState == 0 ? MENU_SIZE-1 : menuState - 1;
    }else if (lcdKey == BTN_SELECT){
      if (menuState == 1){
        state = 2;
      }else if (menuState == 2){
        led_state = !led_state;
        forceRefresh();
      }else if (menuState == 0){
        alarm_state = !alarm_state;
        forceRefresh();
      }else if (menuState == 3){
        THRESHOLD = 1000;
        led_state = true;
        alarm_state = true;
        forceRefresh();
        display("Reset", "Complete");
        delay(1000);
      }
    }
  }
  else if (state == 2) { 
    display(THRESHOLD_STR, String(THRESHOLD));

    if(lcdKey == BTN_DOWN){
      THRESHOLD -= 5;
      forceRefresh();
    }else if (lcdKey == BTN_UP){
      THRESHOLD += 5;
      forceRefresh();
    }else if (lcdKey == BTN_SELECT){
      state = 0;
    }
  }
  
  switch(lcdKey) {
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
}
