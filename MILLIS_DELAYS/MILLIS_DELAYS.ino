const int xPin = A0;  // X-axis connected to A0
const int yPin = A1;  // Y-axis connected to A1
const int zPin = A2;  // Z-axis connected to A2

// ADXL335 Characteristics
const float zeroG = 1.65; // Zero-g voltage (1.65V for 3.3V supply)
const float sensitivity = 0.330; // Sensitivity (330mV per g)
const float vRef = 3.3; // Reference voltage (3.3V)

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
}

void loop() {
  // Read ADC values (0-1023)
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);
  int zRaw = analogRead(zPin);

  // Convert ADC value to voltage
  float xVoltage = (xRaw * vRef) / 1024.0;
  float yVoltage = (yRaw * vRef) / 1024.0;
  float zVoltage = (zRaw * vRef) / 1024.0;

  // Convert voltage to acceleration (g)
  float xG = (xVoltage - zeroG) / sensitivity;
  float yG = (yVoltage - zeroG) / sensitivity;
  float zG = (zVoltage - zeroG) / sensitivity;

  // Print values to Serial Monitor
  Serial.print("X: "); Serial.print(xG); Serial.print(" g, ");
  Serial.print("Y: "); Serial.print(yG); Serial.print(" g, ");
  Serial.print("Z: "); Serial.print(zG); Serial.println(" g");

  delay(500);
}
