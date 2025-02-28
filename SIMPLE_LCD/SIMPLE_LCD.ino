#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#inclue "LCD.h"
// Set the I2C address of the LCD (usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();       // Initialize LCD
  lcd.backlight();  // Turn on the backlight

  lcd.setCursor(0, 0);
  lcd.print("HI!");

  lcd.setCursor(3, 1);
  lcd.print("I2C LCD Example");
}

void loop() {
  // You can add your own functionality here
}
