#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // dimensions of the display
  lcd.setCursor(9, 0); // position of the cursor
  lcd.println("test");
}

void loop() {
  // put your main code here, to run repeatedly:

}
