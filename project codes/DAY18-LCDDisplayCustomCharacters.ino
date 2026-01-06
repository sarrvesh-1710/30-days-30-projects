#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

byte customChar[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  lcd.setCursor(0, 0);
  lcd.print("LCD1602 Ready");
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
}

void loop() {}
