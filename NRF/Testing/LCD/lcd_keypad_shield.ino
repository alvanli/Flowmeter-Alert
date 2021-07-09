#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int lcdKey = 0;

const int btnSelect = A0;
const int btnUp = A1;
const int btnDown = A2;
const int btnBack = A3;
const int btnReset = A4;

const int btnPins[] = {A0, A1, A2, A3, A4};

String message = "alvin told me to test a ten word sentence lol";

int readLCDButtons() {
  
  for(int i = 0; i < 1; i++) {
    //Serial.println(analogRead(btnPins[0]));
    delay(1000);
    Serial.println(btnPins[0]);
    if (analogRead(btnPins[i] < 1010)) {
      return btnPins[i];
    }
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.println(message);

  pinMode(btnSelect, INPUT); 
  pinMode(btnUp, INPUT); 
  pinMode(btnDown, INPUT); 
  pinMode(btnBack, INPUT); 
  pinMode(btnReset, INPUT); 
}

void loop() {
  for (int positionCounter = 0; positionCounter < message.length(); positionCounter++) {
    lcd.scrollDisplayLeft();
    //delay(750);
  }
  
  lcdKey = readLCDButtons();
  switch(lcdKey) {
    case A0: {
      Serial.println("select");
      break;
    }
    case A1: {
      Serial.println("up");
      break;
    }
    case A2: {
      Serial.println("down");
      break;
    }
    case A3: {
      Serial.println("back");
      break;
    }
    case A4: {
      Serial.println("reset");
      break;
    }
    default: 
      Serial.print("default");
  }
}
