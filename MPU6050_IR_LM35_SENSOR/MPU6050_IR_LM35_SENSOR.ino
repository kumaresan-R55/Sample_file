#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<MPU6050.h>

#define LED_PIN1 9
#define IR_SENSOR 2
#define LED_PIN2 3
#define LED_PIN3 6
#define LM35_SENSOR A0


LiquidCrystal_I2C lcd(0x27,16,2);
MPU6050 mpu;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 lcd.backlight(); 
  lcd.init();
  mpu.initialize();
  pinMode(LED_PIN1,OUTPUT);
  pinMode(IR_SENSOR,INPUT);
  pinMode(LED_PIN2,OUTPUT);
  pinMode(LED_PIN3,OUTPUT);
  pinMode(LM35_SENSOR ,OUTPUT);

  if(!mpu.testConnection())
  {
    Serial.println("MPU6050 connection failed!..");
    while(1);
  }
  Serial.println("MPU6050 connection passed..");
}

void loop() {
 
  lcd_currentdisplay();
  mpu6050_module();
  ir_sensor();
  lm35_sensor();


}
void lcd_currentdisplay()
{
    //lcd.setCursor(0, 0);
    //lcd.print("Hello, Arduino!"); // Print text on row 1
    //delay(2000);
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("I2C LCD Working!"); // Print text on row 2
        //delay(2000);
    //lcd.clear();

}
void mpu6050_module()
{ 
  int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.print("AccelX: "); Serial.print(ax);
    Serial.print(" | AccelY: "); Serial.print(ay);
    Serial.print(" | AccelZ: "); Serial.println(az);
     lcd.setCursor(0, 0);
    lcd.print("Ax: "); lcd.print(ax);
    lcd.print("Ay: "); lcd.print(ay);
    delay(1000);
    lcd.clear();
    // If tilt is detected (change in acceleration)
    if (abs(ax) > 15000 || abs(ay) > 15000) {
        digitalWrite(LED_PIN1, HIGH);  // Turn LED ON
    } else {
        digitalWrite(LED_PIN1, LOW);   // Turn LED OFF
    }
}
void ir_sensor()
{
  int SENSOR_VALUE=digitalRead(IR_SENSOR);
  if(SENSOR_VALUE==0)
  {
    digitalWrite(LED_PIN2,HIGH);
    delay(1000);
    }
  
  else
  {
    digitalWrite(LED_PIN2,LOW);
  }
}
void lm35_sensor()
{
  int sensorValue=analogRead(LM35_SENSOR);
  float temperature = (sensorValue * 5.0 * 100.0) / 1024.0; // Convert to Celsius
  lcd.setCursor(0,0);
   lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  
  delay(1000);
  lcd.clear();
  if (temperature > 30) {  // Adjust threshold as needed
    digitalWrite(LED_PIN3, HIGH); // Turn on LED
   
  } else {
    digitalWrite(LED_PIN3, LOW);  // Turn off LED
  }

  delay(1000); // Wait for 1 second before next reading
}


