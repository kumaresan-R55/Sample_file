#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char* ssid = "Airtel_jasm_1011";
const char* password = "air63623";
const char* server = "http://yourserver.com/gps";  // Change this to your actual server URL

SoftwareSerial arduinoSerial(4, 5);  // GPIO4 (D2) RX, GPIO5 (D1) TX with Arduino

void setup() {
    Serial.begin(115200);
    arduinoSerial.begin(9600);
  

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
}

void loop() {
    if (arduinoSerial.available()) {
        String gpsData = arduinoSerial.readStringUntil('\n');
        Serial.println("Received from Arduino: " + gpsData);

        if (WiFi.status() == WL_CONNECTED) {
            WiFiClient client;  // ✅ Create WiFiClient object
            HTTPClient http;
            http.begin(client, server);  // ✅ Use client in http.begin()
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");

            String postData = "gpsData=" + gpsData;
            int httpResponseCode = http.POST(postData);
            
            Serial.print("Server Response: ");
            Serial.println(httpResponseCode);

            http.end();
        } else {
            Serial.println("WiFi Disconnected!");
        }

        delay(2000);  // Send every 2 seconds
    }     
}
