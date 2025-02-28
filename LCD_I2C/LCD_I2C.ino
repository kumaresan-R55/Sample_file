#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define B_PIN1 8
#define B_PIN2 9

// Initialize LCD (I2C Address: 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize SoftwareSerial
SoftwareSerial swSerial(B_PIN1, B_PIN2);


int in1pin = 2;
int in2pin = 3;
int in3pin = 4;
int in4pin = 5;
int in1pin_1= 6;
int in2pin_1 = 7;  // connections to H-Bridge, clockwise / counter

char receivedChar;        // store info
boolean newData = false;  // create a true/false statement

void setup() {

  pinMode(in1pin, OUTPUT);
  pinMode(in2pin, OUTPUT);  // set pins to OUTPUTS
  pinMode(in3pin, OUTPUT);
  pinMode(in4pin, OUTPUT);
  pinMode(in1pin_1, OUTPUT);
  pinMode(in2pin_1, OUTPUT);

  lcd.init();       // Initialize LCD
  lcd.backlight();  // Turn on the backlight
  
  Serial.begin(9600);  // start up serial communication
  swSerial.begin(9600);

  Serial.println("READY");
}

void loop() {

  lcd.setCursor(0, 1);
  lcd.print("Waiting.....");

  recvData();  // read and store data

  moveMotor();  // move motor according to data and then reset
}

void recvData() {

  if (swSerial.available() > 0) {  // if the serial monitor has a reading

    receivedChar = swSerial.read();  // set char to be what is read
    newData = true;                // make statement true
  }
}

void moveMotor() {

  int motordirection = (receivedChar - '0');  // turn recieved data into usable form and give it a name

  while (newData == true) {

    Serial.println(motordirection);  // print motor direction

    if (motordirection == 1) {  // if it reads 1...

      digitalWrite(in1pin, HIGH);  // turn motor one way
      digitalWrite(in2pin, LOW);
      lcd.setCursor(0, 0);
      lcd.print("Analgesics");
   
      delay(2000);
      lcd.clear();

      digitalWrite(in1pin, LOW);  // motor is off
      digitalWrite(in2pin, LOW);

    }
    else if (motordirection == 2) {  // if it reads 2...
     digitalWrite(in3pin, LOW);  // turn motor other way
     digitalWrite(in4pin, HIGH);
     lcd.setCursor(0, 0);
     lcd.print("Antibiotics");

     delay(2000);
     lcd.clear();
     digitalWrite(in3pin, LOW);  // motor is off
     digitalWrite(in4pin, LOW);

    }

    else if (motordirection == 3) {  // if it reads 3...

      digitalWrite(in1pin_1, LOW);  // turn motor other way
      digitalWrite(in2pin_1,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Antipyretics");

      delay(2000);
      lcd.clear();
      digitalWrite(in1pin_1, LOW);  // motor is off
      digitalWrite(in2pin_1, LOW);

    }

    else {  // if nothing is read

      digitalWrite(in1pin, LOW);  // motor is off
      digitalWrite(in2pin, LOW);
    }

    newData = false;  // reset value to false
  }
}