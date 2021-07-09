#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define btnRight 0
#define btnUp 1
#define btnDown 2
#define btnLeft 3
#define btnSelect 4
#define btnNone 5

int lcdKey = 0;
int acdKeyIn = 0;

String message = "alvin told me to test a ten word sentence lol";

int readLCDButtons() {
  acdKeyIn = analogRead(0);
  if (acdKeyIn > 1000) return btnNone;
  if (acdKeyIn < 50 ) return btnRight;
  if (acdKeyIn < 195) return btnUp;
  if (acdKeyIn < 380) return btnDown;
  if (acdKeyIn < 555) return btnLeft;
  if (acdKeyIn < 790) return btnSelect;
  return btnNone;
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void loop() {
  //lcd.setCursor(9, 1);
  //lcd.print(millis()/1000);

  for (int positionCounter = 0; positionCounter < message.length(); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(750);
  }
  
  lcdKey = readLCDButtons();
  switch(lcdKey) {
    case btnRight: {
      break;
    }
    case btnLeft: {
      break;
    }
    case btnUp: {
      break;
    }
    case btnDown: {
      break;
    }
    case btnSelect: {
      break;
    }
    case btnNone: {
      break;
    }
  }
}
