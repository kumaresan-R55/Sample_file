#define RELAY_PIN 2
#define KEY_PIN 7


void setup() {
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(KEY_PIN,INPUT_PULLUP);

}

void loop() {
   int KEY_VALUE=digitalRead(KEY_PIN);
   if(KEY_VALUE==LOW)
   {
      digitalWrite(RELAY_PIN,HIGH);
   }
   else
   {
    digitalWrite(RELAY_PIN,LOW);
   }  
}
