#include <ESP8266WiFi.h>

const char* ssid = "VODAFONE"; // Your WiFi Name
const char* password = "kCPMAj7t";  // Your WiFi Password

void setup() {
  Serial.begin(115200);
  delay(10); 

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing to do here
}

