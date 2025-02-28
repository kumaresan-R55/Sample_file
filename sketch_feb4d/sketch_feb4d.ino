#include <NewPing.h>

// Constants for HC-SR04 ultrasonic sensor
#define TRIGGER_PIN 11  // Input pin for HC-SR04
#define ECHO_PIN 12     // Output pin for HC-SR04
#define SAFE_DIST 8     // Desired distance between robot and object (in cm)
#define MAX_RANGE 100   // Maximum range for ultrasonic sensor

// Create NewPing object for ultrasonic sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_RANGE);
int distance;

// Pin definitions for DC motors controlled by L298N
#define IN1 7
#define IN2 8
#define IN3 4
#define IN4 5
#define ENA 2  // Enable pin for motor A
#define ENB 6  // Enable pin for motor B

// Pin definitions for joystick
#define JOY_X A0 // X-axis pin
#define JOY_Y A1 // Y-axis pin
#define JOY_BTN 9 // Button pin

void setup() {
  // Motor pins setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Joystick pin setup
  pinMode(JOY_BTN, INPUT_PULLUP); // Button with internal pull-up

  // Initialize motor speeds
  analogWrite(ENA, 255); // Full speed for motor A
  analogWrite(ENB, 255); // Full speed for motor B
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMovement() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void loop() {
  int xValue = analogRead(JOY_X); // Read X-axis value
  int yValue = analogRead(JOY_Y); // Read Y-axis value
  bool buttonPressed = digitalRead(JOY_BTN) == LOW;

  // Define dead zone to prevent unwanted movement
  int deadZone = 100;
  int center = 512;

  if (yValue > center + deadZone) {
    moveForward();
  } else if (yValue < center - deadZone) {
    moveBackward();
  } else if (xValue > center + deadZone) {
    turnRight();
  } else if (xValue < center - deadZone) {
    turnLeft();
  } else {
    stopMovement();
  }

  // Check if joystick button is pressed (for additional functionality)
  if (buttonPressed) {
    // Example: Stop robot when button is pressed
    stopMovement();
  }
  delay(100); // Small delay to avoid erratic movements
}
