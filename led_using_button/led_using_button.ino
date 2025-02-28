
#define BUTTON1 2  // Button 1 controls LED1
#define BUTTON2 3  // Button 2 controls LED2
#define BUTTON3 4  // Button 3 controls LED3
#define BUTTON4 5  // Button 4 controls LED4

#define LED1 6  // LED 1 on pin 6
#define LED2 7  // LED 2 on pin 7
#define LED3 8  // LED 3 on pin 8
#define LED4 9  // LED 4 on pin 9

void setup() {
    pinMode(BUTTON1, INPUT_PULLUP); // Enable internal pull-up resistor
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
    pinMode(BUTTON4, INPUT_PULLUP);
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
}

void loop() {
    // Read each button and control its respective LED
    digitalWrite(LED1, !digitalRead(BUTTON1)); // If button pressed, LED turns ON
    digitalWrite(LED2, !digitalRead(BUTTON2));
    digitalWrite(LED3, !digitalRead(BUTTON3));
    digitalWrite(LED4, !digitalRead(BUTTON4));
}
