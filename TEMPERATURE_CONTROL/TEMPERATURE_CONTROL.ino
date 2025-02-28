#include <LiquidCrystal.h>
#include <max6675.h>

// LCD Setup (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// MAX6675 Thermocouple Setup (SO, CS, SCK)
int thermoDO = 2;
int thermoCS = 3;
int thermoCLK = 4;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Solid State Relay (SSR)
int ssrPin = 6;
float setTemperature = 50.0; // Default setpoint

// Button Pins
int increaseButton = A0;
int decreaseButton = A1;
int resetButton = A2;

void setup() {
    lcd.begin(16, 2); // Initialize LCD
    pinMode(ssrPin, OUTPUT);
    digitalWrite(ssrPin, LOW); // Turn off SSR initially

    pinMode(increaseButton, INPUT_PULLUP);
    pinMode(decreaseButton, INPUT_PULLUP);
    pinMode(resetButton, INPUT_PULLUP);

    lcd.setCursor(0, 0);
    lcd.print("Temp Control");
    delay(2000);
    lcd.clear();
}

void loop() {
    float tempC = thermocouple.readCelsius(); // Read temperature

    // Read button states
    if (digitalRead(increaseButton) == LOW) {
        setTemperature += 1.0;
        delay(200); // Debounce delay
    }
    if (digitalRead(decreaseButton) == LOW) {
        setTemperature -= 1.0;
        delay(200); // Debounce delay
    }
    if (digitalRead(resetButton) == LOW) {
        setTemperature = 50.0; // Reset to default
        delay(200);
    }

    // Display temperature and setpoint
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempC);
    lcd.print(" C  ");

    lcd.setCursor(0, 1);
    lcd.print("Set: ");
    lcd.print(setTemperature);
    lcd.print(" C  ");

    // Control SSR (Heater)
    if (tempC < setTemperature) {
        digitalWrite(ssrPin, HIGH); // Heater ON
    } else {
        digitalWrite(ssrPin, LOW); // Heater OFF
    }

    delay(500); // Update every 500ms
}
