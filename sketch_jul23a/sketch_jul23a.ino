#include <Wire.h>

// I2C address of the CJMCU-30205
#define TEMP_SENSOR_ADDR 0x4F

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Initialize I2C communication
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

    // Check if the sensor output format is signed or unsigned
    int16_t tempData = (msb << 8) | lsb; // Combine the two bytes into a single 16-bit value
    if (tempData & 0x8000) { // If the MSB is 1, it is a negative value
      tempData = ~tempData + 1; // Perform two's complement to get the negative value
      tempData = -tempData;
    }

    float temperature = tempData * 0.0625; // Convert to Celsius (assuming the sensor outputs in 0.0625 degree increments)
    return temperature;
  } else {
    return NAN; // Return Not-A-Number if no data is available
  }
}



