/*
 * LAB Name: Arduino I2C LCD 20x4 Example
 * Author: Khaled Magdy
 * For More Info Visit: www.DeepBlueMbedded.com
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C MyLCD(0x08, 16, 2); // Creates I2C LCD Object With (Address=0x27, Cols=20, Rows=4)
 
void setup()
{
  MyLCD.init();
  MyLCD.backlight();
  MyLCD.setCursor(0, 0);
  MyLCD.print("    Hello World!");
  MyLCD.setCursor(0, 1);
  MyLCD.print("    I2C LCD 20x4");

}
 
void loop()
{
}