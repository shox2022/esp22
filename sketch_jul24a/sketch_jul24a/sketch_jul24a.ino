#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

const char* ssid = "VODAFONE";      
const char* password = "kCPMAj7t";  

const char* serverName = "http://localhost/phpmyadmin/C:\xampp\htdocs\test.php";  

const int TEMP_SENSOR_ADDR = 0x4F;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float temperature = readTemperature(TEMP_SENSOR_ADDR);
  String patientName = "Arbri"; // Replace with actual patient name

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      String postData = "sensor_value=" + String(temperature) + "&patient_name=" + patientName;
      
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
      Serial.println("WiFi Disconnected");
    }
  } else {
    Serial.println("Failed to read temperature");
  }

  delay(10000); // Wait for 10 seconds before next reading
}

float readTemperature(uint8_t address) {
  Wire.beginTransmission(address);
  Wire.write(0x00); 
  Wire.endTransmission();

  Wire.requestFrom(address, 2);

  if (Wire.available() == 2) {
    byte msb = Wire.read();
    byte lsb = Wire.read();

    int16_t tempData = (msb << 8) | lsb;
    if (tempData & 0x8000) {
      tempData = ~tempData + 1;
      tempData = -tempData;
    }

    float temperature = tempData * 0.0625;
    return temperature;
  } else {
    return NAN;
  }
}


