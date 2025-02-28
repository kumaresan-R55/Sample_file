#include <Wire.h>

int pwmPin0 = 9;  
int pwmPin1 = 10; 

void setup() {
  pinMode(pwmPin0, OUTPUT);
  pinMode(pwmPin1, OUTPUT);
  Wire.begin(8);           // Initialize as I2C slave at address 8
  Wire.onReceive(receiveEvent); // Register event for receiving data
  Serial.print(9600);
}

void receiveEvent(int bytes) {

  while (Wire.available() >= 2) {
    int channel = Wire.read();   // Read channel identifier
    int pwmValue = Wire.read();    // Read PWM value

    // Update the corresponding PWM output
    if (channel == 0) {
      analogWrite(pwmPin0, pwmValue);
      Serial.print("channel 0 Value");
      Serial.println("pwmvalue");
    } else if (channel == 1) {
      analogWrite(pwmPin1, pwmValue);
      Serial.print("channel 1 Value");
      Serial.println("pwmvalue");
    }
  }
}
  
void loop() {
  
}