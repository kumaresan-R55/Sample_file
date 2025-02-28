#include <SoftwareSerial.h>

#define HC12_TX 3  // HC-12 TX Pin (Arduino TX)
#define HC12_RX 2  // HC-12 RX Pin (Arduino RX)
#define RELAY_IN1 8
#define RELAY_IN2 9
#define RELAY_IN3 10
#define RELAY_IN4 11
#define MOSFET_PIN 6

SoftwareSerial hc12(HC12_TX, HC12_RX);  // HC-12 Serial Communication

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);

  pinMode(RELAY_IN1, OUTPUT);
  pinMode(RELAY_IN2, OUTPUT);
  pinMode(RELAY_IN3, OUTPUT);
  pinMode(RELAY_IN4, OUTPUT);
  pinMode(MOSFET_PIN, OUTPUT);

  digitalWrite(RELAY_IN1, LOW);
  digitalWrite(RELAY_IN2, LOW);
  digitalWrite(RELAY_IN3, LOW);
  digitalWrite(RELAY_IN4, LOW);
}

void loop() {
  if (hc12.available()) {
    char motorSpeed = hc12.read();  // Read joystick value



    Serial.print("Received Motor Speed: ");
    Serial.println(motorSpeed);

    if (motorSpeed == '1') {  // Forward
      digitalWrite(RELAY_IN1, HIGH);
      digitalWrite(RELAY_IN2, LOW);
      digitalWrite(RELAY_IN3, HIGH);
      digitalWrite(RELAY_IN4, LOW);
      Serial.println("forward...");

    } else if (motorSpeed == '2') {  // back
      digitalWrite(RELAY_IN1, LOW);
      digitalWrite(RELAY_IN2, HIGH);
      digitalWrite(RELAY_IN3, LOW);
      digitalWrite(RELAY_IN4, HIGH);
      Serial.println("backward...");
    } else if (motorSpeed == '3') {  // right
      digitalWrite(RELAY_IN1, LOW);
      digitalWrite(RELAY_IN2, HIGH);
      digitalWrite(RELAY_IN3, HIGH);
      digitalWrite(RELAY_IN4, LOW);
      Serial.println("left...");
    }

    else if (motorSpeed == '4') {  // left
      digitalWrite(RELAY_IN1, HIGH);
      digitalWrite(RELAY_IN2, LOW);
      digitalWrite(RELAY_IN3, LOW);
      digitalWrite(RELAY_IN4, HIGH);
      Serial.println("right...");
    } else if (motorSpeed == '5') {  // Stop
      digitalWrite(RELAY_IN1, LOW);
      digitalWrite(RELAY_IN2, LOW);
      digitalWrite(RELAY_IN3, LOW);
      digitalWrite(RELAY_IN4, LOW);
      Serial.println("Stopped");
    }
  }
  if (Serial.available()) {        // Check if data is available
    char command = Serial.read();  // Read character

    if (command == 'O') {
      digitalWrite(MOSFET_PIN, HIGH);  // Turn motor ON
      Serial.println("Motor ON");

      delay(2000);
      Serial.println("Motor OFF");
      digitalWrite(MOSFET_PIN, LOW);  // Turn motor ON
    }
  }
}
