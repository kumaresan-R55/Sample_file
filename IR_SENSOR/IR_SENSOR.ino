#define IR_SENSOR_PIN 2  // IR sensor connected to digital pin 2
#define LED_PIN  3       // LED connected to digital pin 3

void setup() {
    pinMode(IR_SENSOR_PIN, INPUT);  // Set IR sensor pin as input
    pinMode(LED_PIN, OUTPUT);       // Set LED pin as output
    Serial.begin(9600);             // Start Serial Monitor
}

void loop() {
    int sensorValue = digitalRead(IR_SENSOR_PIN); // Read IR sensor output

    if (sensorValue == HIGH) {  // If object detected
        digitalWrite(LED_PIN, HIGH);  // Turn ON LED
        Serial.println("Object detected!");
    } else {
        digitalWrite(LED_PIN, LOW);   // Turn OFF LED
        Serial.println("No object detected");
    }

    delay(100);  // Small delay to prevent rapid toggling
}
