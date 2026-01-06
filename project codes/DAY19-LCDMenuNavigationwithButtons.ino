#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define UP_BTN 8
#define DOWN_BTN 9
#define SEL_BTN 10

int menuIndex = 0;
const int menuItems = 2;

void setup() {
  lcd.begin(16, 2);

  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(SEL_BTN, INPUT_PULLUP);

  displayMenu();
}

void loop() {
  if (digitalRead(UP_BTN) == LOW) {
    menuIndex = (menuIndex - 1 + menuItems) % menuItems;
    displayMenu();
    delay(200);
  }

  if (digitalRead(DOWN_BTN) == LOW) {
    menuIndex = (menuIndex + 1) % menuItems;
    displayMenu();
    delay(200);
  }

  if (digitalRead(SEL_BTN) == LOW) {
    lcd.clear();
    lcd.print("Selected:");
    lcd.setCursor(0, 1);
    if (menuIndex == 0) lcd.print("LED Control");
    if (menuIndex == 1) lcd.print("Sensor Data");
    delay(800);
    displayMenu();
  }
}

void displayMenu() {
  lcd.clear();
  if (menuIndex == 0) {
    lcd.print("> LED Control");
    lcd.setCursor(0, 1);
    lcd.print("  Sensor Data");
  } else {
    lcd.print("  LED Control");
    lcd.setCursor(0, 1);
    lcd.print("> Sensor Data");
  }
}
