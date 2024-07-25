#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define TEMP_SENSOR_ADDR 0x4F  

const char* ssid = "VODAFONE";       
const char* password = "kCPMAj7t"; // Your WiFi Password
const char* serverName = "http://localhost/phpmyadmin/"; 

WiFiClient client;  // Create a WiFiClient object

void setup() {
  Serial.begin(115200);       // Start the Serial communication at baud rate 115200
  Wire.begin(D1, D2);         // Initialize I2C communication on SDA (D1) and SCL (D2) pins
  Serial.println("Temperature Sensor Test");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  Wire.beginTransmission(TEMP_SENSOR_ADDR);
  Wire.write(0x00);  // Point to temperature register
  Wire.endTransmission();
  Wire.requestFrom(TEMP_SENSOR_ADDR, 2);  // Request 2 bytes from the sensor

  if (Wire.available() == 2) {
    int16_t rawTemp = (Wire.read() << 8) | Wire.read();
    rawTemp >>= 4;  // Right shift to get 12-bit value

    float temperature = rawTemp * 0.0625;  // TMP102 has 0.0625 degree C per LSB

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Send data to server
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.setTimeout(10000);  // Increase timeout
      http.begin(client, serverName);  // Use the WiFiClient object and server URL

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Prepare data to send
      String postData = "sensor_value=" + String(temperature) + "&patient_name=JohnDoe";

      // Send HTTP POST request
      int httpResponseCode = http.POST(postData);

      // Check HTTP response
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      // Free resources
      http.end();
    }
  } else {
    Serial.println("Error reading temperature!");
  }

  delay(10000);  // Wait for 10 seconds before the next reading
}






