#include <LiquidCrystal.h>
#include "C:/Users/brian/Desktop/Flowmeter-Alert/library/detectButton.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "C:/Users/brian/Desktop/Flowmeter-Alert/library/pitches.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int lcdKey = 0;

String warning_string = "DEFAULT";
const String ALARM_STR = "Alarm";
const String THRESHOLD_STR = "Set Threshold";
const String LED_STR = "LED";
const String RESET_STR = "RESET";
const String BACK = "Back";
const String MENU_ITEMS[] = {ALARM_STR, THRESHOLD_STR, LED_STR, RESET_STR, BACK};
const int MENU_SIZE = 5;
int THRESHOLD = 1000;

int state = 0; // 0: Warning, 1: Menu, 2: Thres Menu
int prevState = 0;
int menuState = 2; // 0: ALARM_STR, 1: THRESHOLD_STR, 2: LED_STR, 3: RESET, 4: BACK
boolean led_state = true;
boolean alarm_state = true;

String prevMsg1 = "";
String prevMsg2 = "";

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

bool tooHigh = false;
bool tooLow = false;

unsigned long lastTime = 0;
int currNote = 0;
bool playing = false;

int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, END
};

// note durations: 8 = quarter note, 4 = 8th note, etc.
int noteDurations[] = {       //duration of the notes
  2, 2, 2, 2, 1, 2, 2, 1, 2
};

int speed=90;  //higher value, slower notes

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // dimensions of the display
  lcd.setCursor(0, 0); // position of the cursor
  lcd.print(warning_string);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

  pinMode(A2, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();

  lastTime = millis();
}


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

void showMenu(int lcdKey) {
  if (state == 0){ 
    displayLCD(warning_string, "");
    if (lcdKey == BTN_SELECT) {
      state = 1;
      prevState = 0;
    }
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
      }else if (menuState == 4){
        state = 0;
        prevState = 1;
      }
    }
  }
  else if (state == 2) { 
    displayLCD(THRESHOLD_STR, String(THRESHOLD));

    if(lcdKey == BTN_DOWN){
      THRESHOLD -= 5;
      forceRefresh();
    }else if (lcdKey == BTN_UP){
      THRESHOLD += 5;
      forceRefresh();
    }else if (lcdKey == BTN_SELECT){
      state = 0;
      prevState = 2;
    }
  }
}

void loop() {
  lcdKey = readLCDButtons();
  showMenu(lcdKey);

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

  alarmCheck();

  if (radio.available()){              //Looking for the data.
    int res1 = 0;
    int res2 = 0; //Saving the incoming data
    radio.read(&res1, sizeof(res1));    //Reading the data
    radio.read(&res2, sizeof(res2)); 
    //Serial.println("res 1: " + String(res1));
    //Serial.println("res 2: " + String(res2));
    getBallLocation(res1, res2);
    Serial.println("Too high?: " + String(tooHigh));
    Serial.println("Too low?: " + String(tooLow));
    if (tooHigh && !tooLow) {
      warning_string = "TOO HIGH";
      playing = true; // Toggle bool to play tone
    } else if (!tooHigh && tooLow) {
      warning_string = "TOO LOW";
      playing = true; // Toggle bool to play tone
    } else if (!tooHigh && !tooLow) {
      warning_string = "GOOD";
    }
    //if (tooHigh && tooLow){
      //Serial.println("ERROR: ball is too high and too low at the same time");
    //}
  }
}

void getBallLocation(int res1, int res2) {
  if (res1 == 1){
    tooHigh = true;
  }
  if (res2 == 1){
    tooLow = true;
  }
  if (res1 == -1){
    tooHigh = false;
  }
  if (res2 == -1){
    tooLow = false;
  }
}

/*
void playAlarm(){
  if (alarm_state) {
   for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {
      int noteDuration = speed*noteDurations[thisNote];
      tone(A2, melody[thisNote],noteDuration*.95);
      Serial.println(melody[thisNote]);
      
      delay(noteDuration);
      if (millis() - lastInterruptTime > noteDuration) noTone(A2);
  
    } 
  }
}
*/

// Does alarm stuff - check time, play, and stop
void alarmCheck() {
  if (alarm_state) {
    if (playing) {
      int noteDuration = speed*noteDurations[currNote]; // set dur
      if ((millis() - lastTime) >= noteDuration) {
        if (melody[currNote + 1] == -1) { // reset vars and stop tone if playing ended
          playing = false; 
          currNote = 0;
          lastTime = millis();
          noTone(A2);
        } else { // increment to next note
          currNote += 1;
          noteDuration = speed*noteDurations[currNote];
          lastTime = millis();
        }
      } else { // play tone
        tone(A2, melody[currNote]); // this'll constantly send a freq to the pin i hope it doesnt lag
      }
    } else {
      lastTime = millis(); // keep time counter updated when alarm not playing
    }
  } else {
    lastTime = millis(); // keep time counter updated when alarm not playing
    noTone(A2); // make sure to turn off if alarm is set to not play
  }
}
