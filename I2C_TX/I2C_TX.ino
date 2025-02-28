#include<Wire.h>


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

}

void loop() {

  Wire.beginTransmission(8);
  Wire.write("HELLO SLAVE...");
  Wire.endTransmission();
  Serial.println("DATA SEND TO SLAVE");
  
}
