#include <Servo.h>
#include <NewPing.h>

// Constants for HC-SR04 ultrasonic sensor
#define TRIGGER_PIN 11  // Input pin for HC-SR04
#define ECHO_PIN 12     // Output pin for HC-SR04
#define SAFE_DIST 8     // Desired distance between robot and object (in cm)
#define MIN_ANGLE 0     // Minimum angle for servo rotation
#define MAX_ANGLE 180   // Maximum angle for servo rotation
#define ANGLE_STEP 30   // Step size for rotating the sensor

// Create servo objects for the robotic arm and sensor rotation
Servo servoA; // Arm Servo: Moves arm forwards and backwards
Servo servoB; // Base Servo: Moves entire arm left and right
Servo servoC; // Arm Servo: Moves arm up and down
Servo servoD; // Claw Servo: Opens and closes the claw
Servo sensorServo; // Servo for rotating the ultrasonic sensor

// Create NewPing object for ultrasonic sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, 100);  // Max range 100 cm
int distance;  // Used in loop
int angleA, angleC;  // Angle values for moving arm forward/backward and up/down

// Pin definitions for DC motors controlled by L298N
#define IN1 7
#define IN2 8
#define IN3 4
#define IN4 5
#define ENA 2  // Enable pin for motor A
#define ENB 6  // Enable pin for motor B

// Initialize motor pins
void setup() {
  // Attach servos to corresponding PWM pins
  servoA.attach(9);  
  servoB.attach(6);  
  servoC.attach(5);  
  servoD.attach(3);  
  sensorServo.attach(10); // Attach the sensor rotation servo

  // Motor pins setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize motor speeds
  analogWrite(ENA, 255); // Full speed for motor A
  analogWrite(ENB, 255); // Full speed for motor B

  // Reset arm position
  resetArm();
}

void resetArm() {
  // Arm resting position
  servoA.write(90);   // Central position
  servoB.write(90);   // Central position
  servoC.write(180);  // Fully up
  servoD.write(90);   // Neutral claw
}

// Function to control robot's forward movement
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to control robot's backward movement
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Function to stop the robot
void stopMovement() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Function to turn the robot left (rotate in place)
void turnLeft() {
  digitalWrite(IN1, HIGH);  // Motor A backward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Motor B forward
  digitalWrite(IN4, HIGH);
}

// Function to turn the robot right (rotate in place)
void turnRight() {
  digitalWrite(IN1, LOW);  // Motor A forward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);  // Motor B backward
  digitalWrite(IN4, LOW);
}

void grabItem() {
  servoD.write(180);      // Open claw
  delay(1000);            // Wait for 1 sec
  servoA.write(angleA);   // Move arm to calculated distance
  delay(1000);            // Wait for 1 sec
  servoC.write(angleC);   // Move arm down to calculated position
  delay(1000);            // Wait for 1 sec
  servoD.write(110);      // Close claw
  delay(1000);            // Wait for 1 sec
}

void dropItem() {
  servoB.write(180);      // Rotate arm to drop location
  delay(1000);            // Wait for 1 sec
  servoD.write(180);      // Open claw to drop item
  delay(1000);            // Wait for 1 sec
}

void loop() {
  // Rotate the sensor servo to scan for objects
  for (int angle = MIN_ANGLE; angle <= MAX_ANGLE; angle += ANGLE_STEP) {
    sensorServo.write(angle); // Rotate sensor to current angle
    delay(500); // Wait for sensor to stabilize and get a reading
    distance = sonar.ping_cm(); // Get distance from ultrasonic sensor

    if (distance > 0 && distance <= 100) {  // If object is within 100 cm
      // Move towards the object until 8 cm distance
      while (distance > SAFE_DIST) {
        moveForward();        // Move robot towards the object
        delay(100);           // Small delay to prevent continuous loop
        distance = sonar.ping_cm(); // Update distance
      }

      stopMovement(); // Stop when 8 cm distance is reached
      grabItem();     // Grab the item

      resetArm();     // Reset arm position
      delay(1000);    // Wait for 1 sec

      dropItem();     // Drop the item
      resetArm();     // Reset arm position
      delay(1000);    // Wait for 1 sec
      break; // Exit loop after completing the task
    }
  }
}
