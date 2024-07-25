#include <Wire.h>

// I2C address of the CJMCU-30205
#define TEMP_SENSOR_ADDR 0x4F

void setup() {
  Serial.begin(115200); // NodeMCU often uses a higher baud rate
  Wire.begin(D2, D1); // Initialize I2C with SDA and SCL pins for NodeMCU
}

void loop() {
  float temperature = readTemperature(TEMP_SENSOR_ADDR);
  
  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println("Failed to read temperature");
  }

  delay(1000); // Wait for 1 second before reading again
}

float readTemperature(uint8_t address) {
  Wire.beginTransmission(address);
  Wire.write(0x00); // Point to the temperature register
  Wire.endTransmission();

  Wire.requestFrom(address, 2); // Request 2 bytes of data

  if (Wire.available() == 2) {
    byte msb = Wire.read(); // Most significant byte
    byte lsb = Wire.read(); // Least significant byte

    // Combine the two bytes into a single 16-bit value
    int16_t tempData = (msb << 8) | lsb;
    // Convert the data to Celsius
    float temperature = tempData * 0.0625;
    return temperature;
  } else {
    return NAN; // Return Not-A-Number if no data is available
  }
}




