

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include "Protocentral_MAX30205.h"

MAX30205 tempSensor;

const char* ssid = "VODAFONE";        // Replace with your WiFi SSID
const char* password = "kCPMAj7t"; // Replace with your WiFi password
const char* serverUrl = "http://192.168.100.7/save_temperature.php"; // Replace with your server URL

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");

  Wire.begin(D1, D2); // Initialize I2C communication with SDA on D1 and SCL on D2

  // Scan for temperature in every 30 sec until a sensor is found. Scan for both addresses 0x48 and 0x49
  while(!tempSensor.scanAvailableSensors()){
    Serial.println("Couldn't find the temperature sensor, please connect the sensor.");
    delay(30000);
  }

  tempSensor.begin(); // Set continuous mode, active mode
}

void loop() {
  float temp;
  bool success = false;
  
  for (int i = 0; i < 5; i++) { // Retry up to 5 times
    temp = tempSensor.getTemperature(); // Read temperature
    if (temp != 0.0) { // Check if reading is not zero
      success = true;
      break;
    }
    delay(50); // Wait before retrying
  }
  
  if (success) {
    Serial.print(temp, 2);
    Serial.println("'C");

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(client, serverUrl); // Use WiFiClient with the URL
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String postData = "temperature=" + String(temp, 2);
      int httpResponseCode = http.POST(postData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
  } else {
    Serial.println("Failed to read temperature after 5 attempts.");
  }
  
  delay(1000); // Wait 1 second before next reading
}




