#include<Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);

}

void loop() {

  for (int pwmValue = 0; pwmValue <= 255;  pwmValue+=20) {
   Wire.beginTransmission(8);//send to slave address
   Wire.write(0);         // Channel identifier 0
   Wire.write(pwmValue);  // PWM value for channel 0

    // Send data for channel 1 (e.g., LED on pin 10)
    Wire.write(1);             // Channel identifier 1
    Wire.write(255-pwmValue); // PWM value for channel 1
    Wire.endTransmission();
    
    delay(100);
  }
}