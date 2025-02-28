#include <SoftwareSerial.h>

#define HC12_TX  2  // HC-12 TX Pin (Arduino TX)
#define HC12_RX  3  // HC-12 RX Pin (Arduino RX)
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

SoftwareSerial hc12(HC12_TX, HC12_RX); // HC-12 Serial Communication

void setup() {
    Serial.begin(9600);
    hc12.begin(9600);
}

void loop() {
    int xValue = analogRead(JOYSTICK_X); // Read joystick X-axis
    int yValue = analogRead(JOYSTICK_Y); // Read joystick Y-axis

 

    String direction= "5"; // Default to "else"

    // Determine direction
    if (xValue > 600) {
        direction = "2";  // Forward
    } else if (xValue < 400) {
        direction = "1";  // Reverse
    } else if (yValue > 600) {
        direction = "4";  // Right
    } else if (yValue < 400) {
        direction = "3";  // Left
    }
    else{
        direction = "5";  

    }

    // Send direction and speed via HC-12
    hc12.print(direction);

    // Debugging
    Serial.print("Direction: ");
    Serial.println(direction);
  

    delay(100); // Small delay for stability
}
