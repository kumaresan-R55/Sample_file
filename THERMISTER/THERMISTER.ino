#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin Definitions
#define ONE_WIRE_BUS 2     // DS18B20 data pin
#define RELAY_PIN 5        // Relay control pin
#define ENTER_BUTTON 3     // Enter button
#define INC_BUTTON 4       // Increase button
#define DEC_BUTTON 6       // Decrease button

// Temperature Sensor Setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LCD Setup (I2C Address: 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
float measured_temp = 0.0;  // Current temperature
float target_temp = 25.0;   // Default set temperature
bool isSettingMode = false; // Flag for setting mode

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(ENTER_BUTTON, INPUT_PULLUP);
    pinMode(INC_BUTTON, INPUT_PULLUP);
    pinMode(DEC_BUTTON, INPUT_PULLUP);

    Serial.begin(9600);
    sensors.begin();  
    lcd.init();
    lcd.backlight();
    
    lcd.setCursor(0, 0);
    lcd.print("Temp Control");
    delay(2000);
    lcd.clear();
}

void loop() {
    sensors.requestTemperatures();  
    measured_temp = sensors.getTempCByIndex(0); // Read temperature
    
    if (digitalRead(ENTER_BUTTON) == LOW) {
        delay(200); // Debounce
        isSettingMode = !isSettingMode;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(isSettingMode ? "Set Mode: ON" : "Set Mode: OFF");
        delay(1000);
    }

    if (isSettingMode) {
        if (digitalRead(INC_BUTTON) == LOW) {
            target_temp += 0.5;
            delay(200); // Debounce
        }
        if (digitalRead(DEC_BUTTON) == LOW) {
            target_temp -= 0.5;
            delay(200); // Debounce
        }
    } else {
        if (measured_temp >= target_temp) {
            digitalWrite(RELAY_PIN, LOW);  // Turn on relay
        } else {
            digitalWrite(RELAY_PIN, HIGH);   // Turn off relay
        }
    }

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Temp: ");
    lcd.print(target_temp, 1);
    lcd.print((char)223); // Degree symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Cur Temp: ");
    lcd.print(measured_temp, 1);
    lcd.print((char)223);
    lcd.print("C");

    //delay(100); // Small delay for button response
}
