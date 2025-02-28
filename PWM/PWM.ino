int potPin = A0;   
int ledPin = 10;    
int potValue = 0; 
int brightness = 0; 
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  potValue = analogRead(potPin);           // Read potentiometer (0-1023)
  brightness = map(potValue, 0, 1023, 0, 255); // Scale value to 0-255
  analogWrite(ledPin, brightness);          
}
