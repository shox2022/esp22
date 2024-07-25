#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

const char* ssid = "VODAFONE";      // Replace with your WiFi SSID
const char* password = "kCPMAj7t";  // Replace with your WiFi Password

const char* serverName = "http://localhost/phpmyadmin/";  // Replace with your computer's IP address

WiFiClient client;

const int I2C_ADDRESS = 0x4C;  // CJMCU-30205 I2C address

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(D2, D1);  // Initialize I2C (SDA, SCL)
}

float readTemperature() {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(0x00);  // Temperature register
  Wire.endTransmission();
  
  Wire.requestFrom(I2C_ADDRESS, 2);
  if (Wire.available() == 2) {
    int temp = Wire.read() << 8 | Wire.read();
    return temp * 0.02 - 273.15;  // Convert to Celsius
  } else {
    return -999;  // Error value
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = readTemperature();
    if (temperature != -999) {  // Check if the temperature read was successful
      HTTPClient http;
      
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      String postData = "sensor_value=" + String(temperature) + "&patient_name=John Doe";  // Send the temperature and patient name
      
      Serial.println("Sending data to server...");
      int httpResponseCode = http.POST(postData);
      
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print("Response from server: ");
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
      
      http.end();
    } else {
      Serial.println("Failed to read temperature");
    }
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(10000);  // Send data every 10 seconds
}

