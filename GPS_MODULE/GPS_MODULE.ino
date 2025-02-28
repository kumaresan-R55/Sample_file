#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial gpsSerial(4, 3); // GPS module RX, TX
TinyGPSPlus gps;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD

void setup() {
    Serial.begin(9600);
    gpsSerial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("GPS Initializing");
    delay(2000);
    lcd.clear();
}

void loop() {
    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());

        if (gps.location.isUpdated()) {
            // Convert latitude and longitude to degrees, minutes, and direction (N/S, E/W)
            char latDirection = (gps.location.rawLat().negative ? 'S' : 'N');
            char lngDirection = (gps.location.rawLng().negative ? 'W' : 'E');

            int latDegrees = gps.location.rawLat().deg;
            double latMinutes = gps.location.rawLat().billionths / 1000000000.0 * 60;

            int lngDegrees = gps.location.rawLng().deg;
            double lngMinutes = gps.location.rawLng().billionths / 1000000000.0 * 60;

            double altitude = gps.altitude.meters();

            // Display on Serial Monitor
            Serial.print("Latitude: ");
            Serial.print(latDegrees);
            Serial.print("° ");
            Serial.print(latMinutes, 4);
            Serial.print("' ");
            Serial.println(latDirection);

            Serial.print("Longitude: ");
            Serial.print(lngDegrees);
            Serial.print("° ");
            Serial.print(lngMinutes, 4);
            Serial.print("' ");
            Serial.println(lngDirection);

            Serial.print("Altitude: ");
            Serial.print(altitude);
            Serial.println(" m");

            Serial.print("Time: ");
            Serial.print(gps.time.hour());
            Serial.print(":");
            Serial.print(gps.time.minute());
            Serial.print(":");
            Serial.println(gps.time.second());

            Serial.println("-------------------");

            // Display on LCD
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Lat:");
            lcd.print(latDegrees);
            lcd.print(" ");
            lcd.print(latMinutes, 2);
            lcd.print(latDirection);

            lcd.setCursor(0, 1);
            lcd.print("Lng:");
            lcd.print(lngDegrees);
            lcd.print(" ");
            lcd.print(lngMinutes, 2);
            lcd.print(lngDirection);

            delay(2000); // Update every 2 seconds
        }
    }
}
