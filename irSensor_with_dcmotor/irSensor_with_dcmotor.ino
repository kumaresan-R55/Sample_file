

#define IR_SENSOR_PIN 2  // IR sensor connected to digital pin 2
#define inPin1 3    // LED connected to digital pin 3
#define inPin2 4
#define button 5
#define inPin3 6
#define inPin4 7

void setup() {
    pinMode(IR_SENSOR_PIN, INPUT);  // Set IR sensor pin as input
    pinMode(inPin1, OUTPUT);       //
    pinMode(inPin2, OUTPUT); 
    pinMode(inPin3, OUTPUT);
    pinMode(inPin4, OUTPUT);  
    pinMode(button, INPUT); 
    Serial.begin(9600); 
}

void loop() {
    int sensorValue = digitalRead(IR_SENSOR_PIN); // Read IR sensor output
    int pressButton= digitalRead(button);
    char command;

     if (Serial.available() > 0) { // Read from Serial Monitor
          command = Serial.read();
        Serial.write(command);  // Send command to Receiver
    }
     else if(command == 'A')
     {
        digitalWrite(inPin1, HIGH);  
        digitalWrite(inPin2, LOW); 
        Serial.println("forward...");
     }
     
    else if ((sensorValue == 0) && (pressButton==1)) {  // If object detected

        digitalWrite(inPin1, HIGH);  
        digitalWrite(inPin2, LOW); 
       
        Serial.println("forward...");
    }
    else if (sensorValue == 0){
     
        digitalWrite(inPin1, HIGH);  
        digitalWrite(inPin2, LOW); 
       
        Serial.println("forward...");
    }
    else {
        digitalWrite(inPin1, LOW);  
        digitalWrite(inPin2, LOW); 
       
    }
}
