#include <LiquidCrystal.h>
#include "detectButton.h"
#include "pitches.h"


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int lcdKey = 0;

const String WARNING = "WORDS OF WARNING";
const String ALARM_STR = "Alarm";
const String THRESHOLD_STR = "Set Threshold";
const String LED_STR = "LED";
const String RESET_STR = "RESET";
const String BACK_STR = "BACK";
const String CALI_STR = "CALIBRATE";
const String MENU_ITEMS[] = {ALARM_STR, THRESHOLD_STR, LED_STR, RESET_STR, BACK_STR, CALI_STR};
const int MENU_SIZE = 4;
int THRESHOLD = 1000;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // dimensions of the display
  lcd.setCursor(0, 0); // position of the cursor
  lcd.print(WARNING);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

int state = 0; // 0: Warning, 1: Menu, 2: Thres Menu
int prevState = 0;
int menuState = 0; // 0: ALARM_STR, 1: THRESHOLD_STR, 2: LED_STR, 3: RESET_STR, 4: BACK_STR, 5: CALI_STR;
int prevMenuState = 0;
boolean led_state = true;
boolean alarm_state = true;

String prevMsg1 = "";
String prevMsg2 = "";

void displayLCD(String message1, String message2){
  if (!prevMsg1.equals(message1) && !prevMsg2.equals(message2)){
    prevMsg1 = message1;
    prevMsg2 = message2;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message1);
    lcd.setCursor(0, 1);
    lcd.print(message2);
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
  displayLCD(firstMessage, secondMessage);
}

void forceRefresh(){
  prevMsg1 = "";
  prevMsg2 = "";
}

void loop() {
  //lcdKey = readLCDButtons();
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  Serial.println(SW_state);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  //Serial.println(xPosition);
  //Serial.println(yPosition);
  delay(1000);
  if (state == 0){ 
<<<<<<< HEAD:NRF/Testing/LCD/lcd_keypad_shield/lcd_keypad_shield.ino
    displayLCD(WARNING, "");
    if (lcdKey == BTN_SELECT) state = 1;
  }
  else if (state == 1){ 
    mainMenuDisplay(menuState);
    if (yPosition < 100){
      menuState = menuState >= MENU_SIZE -1 ? 0 : menuState + 1;
    }else if (yPosition > 900){
=======
    display(WARNING, "");
    if (lcdKey == BTN_SELECT){
      state = 1;
      prevState = 0;
    }
  }
  else if (state == 1){ 
    mainMenuDisplay(menuState);
    if (lcdKey == BTN_DOWN){
      menuState = menuState >= MENU_SIZE-1 ? 0 : menuState + 1;
    }else if (lcdKey == BTN_UP){
>>>>>>> 0a8c6e4d4db0cc904712fb24cb97a73200462c26:NRF/Testing/LCD/lcd_keypad_shield.ino
      menuState = menuState == 0 ? MENU_SIZE-1 : menuState - 1;
    }else if (SW_state == 0){
      if (menuState == 1){
        state = 2;
        prevState = 1;
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
        displayLCD("Reset", "Complete");
        delay(1000);
        // send reset
      }else if (menuState == 4){
        state = 0;
        prevState = 1;
      }else if (menuState == 5){
        // send cali
      }
    }
  }
  else if (state == 2) { 
<<<<<<< HEAD:NRF/Testing/LCD/lcd_keypad_shield/lcd_keypad_shield.ino
    displayLCD(THRESHOLD_STR, String(THRESHOLD));

    if(yPosition < 100){
=======
    display(THRESHOLD_STR, String(THRESHOLD));
    if(lcdKey == BTN_DOWN){
>>>>>>> 0a8c6e4d4db0cc904712fb24cb97a73200462c26:NRF/Testing/LCD/lcd_keypad_shield.ino
      THRESHOLD -= 5;
      forceRefresh();
    }else if (yPosition > 900){
      THRESHOLD += 5;
      forceRefresh();
    }else if (SW_state == 0){
      state = 0;
      prevState = 2;
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
