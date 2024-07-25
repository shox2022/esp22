#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "VODAFONE";      // Replace with your WiFi SSID
const char* password = "kCPMAj7t";  // Replace with your WiFi Password

const char* serverName = "http://192.168.100.7/test.php";  // Replace with your computer's IP address

WiFiClient client;

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
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(client, serverName);  // Use the new API
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String postData = "sensor_value=123.45";  // Hardcoded fake data
    
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
    Serial.println("WiFi Disconnected");
  }
  
  delay(10000);  // Send data every 10 seconds
}

