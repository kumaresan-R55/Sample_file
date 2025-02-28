#include <Arduino.h>
#include <Servo.h>

// L298N motor driver pins
#define EN_A 10    // Enable Pin for Motor 1
#define IN1   9    // Motor 1 Input Pin 1
#define IN2   8    // Motor 1 Input Pin 2
#define IN3   7    // Motor 2 Input Pin 3
#define IN4   6    // Motor 2 Input Pin 4
#define EN_B  5    // Enable Pin for Motor 2

// Fire sensor pins (Digital)
#define FIRE_R 2   // Fire sensor right
#define FIRE_F 3   // Fire sensor front
#define FIRE_L 4   // Fire sensor left

// Pump and Servo
#define PUMP_PIN A5  // Pump control pin
#define SERVO_PIN 11 // Servo control pin

int motorSpeed = 160;  // Motor speed (0-255)
int s1, s2, s3;        // Fire sensor values
Servo pumpServo;       // Servo for directing pump

void setup() {
    Serial.begin(9600); // Start serial communication

    // Setup pin modes
    pinMode(FIRE_R, INPUT);
    pinMode(FIRE_F, INPUT);
    pinMode(FIRE_L, INPUT);
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);

    // Attach servo to pin
    pumpServo.attach(SERVO_PIN);

    // Set motor speed
    analogWrite(EN_A, motorSpeed);
    analogWrite(EN_B, motorSpeed);

    // Set servo to center (front)
    pumpServo.write(90);
    
    delay(500);
}

void loop() {
    moveForward();  // Move forward first
    delay(500);     // Short delay before checking fire sensors

    s1 = digitalRead(FIRE_R);
    s2 = digitalRead(FIRE_F);
    s3 = digitalRead(FIRE_L);

    // Print sensor values
    Serial.print("Right: "); Serial.print(s1);
    Serial.print(" | Front: "); Serial.print(s2);
    Serial.print(" | Left: "); Serial.println(s3);

    if (s1 == 1) {
        handleFireAtRight();
    } else if (s2 == 1) {
        handleFireAtFront();
    } else if (s3 == 1) {
        handleFireAtLeft();
    }
    delay(10);  // Short delay for responsiveness
}

void handleFireAtRight() {
    Stop();
    pumpServo.write(60);  // Turn servo to the right
    sprayWater();
}

void handleFireAtFront() {
    Stop();
    pumpServo.write(90); // Keep servo at the center
    sprayWater();
}

void handleFireAtLeft() {
    Stop();
    pumpServo.write(120); // Turn servo to the left
    sprayWater();
}

void sprayWater() {
    digitalWrite(PUMP_PIN, HIGH); // Activate pump
    delay(500); // Spray duration
    digitalWrite(PUMP_PIN, LOW);  // Deactivate pump
    moveForward();  // Continue moving forward after extinguishing fire
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

void turnRight() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnLeft() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void Stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
