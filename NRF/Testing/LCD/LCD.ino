#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup(void)
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Humidity & temp");
  delay(2000);
  lcd.clear();
  lcd.print("Starting.....");
  delay(2000);
}

void loop(void)
{
  lcd.setCursor(0, 0);
  lcd.print("No radio Found");

}
