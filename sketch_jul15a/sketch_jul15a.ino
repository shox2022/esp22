#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial espSerial(2, 3); // RX, TX
bool isConnected = false;
unsigned int retryCount = 0;

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);

  Serial.println("Starting ESP8266...");
  espSerial.println("AT+RST");
  delay(2000);
  
  // Test if the module is ready
  espSerial.println("AT");
  delay(1000);
  
  if (espSerial.find("OK")) {
    Serial.println("ESP8266 is ready.");
  } else {
    Serial.println("ESP8266 not responding.");
    while (true); // Halt execution if the ESP8266 is not responding
  }

  espSerial.println("AT+CWMODE=1"); // Set the ESP8266 to station mode
  delay(1000);
}

void loop() {
  Serial.println("Connecting to Wifi");
  
  while (!isConnected) {
    Serial.print(".");
    espSerial.print("AT+CWJAP=\"VODAFONE\",\"kCPMAj7t\"\r\n");
    espSerial.setTimeout(10000); // Set timeout period to 10 seconds
    
    if (espSerial.find("WIFI CONNECTED")) {
      Serial.println("WIFI CONNECTED");
      isConnected = true;
    } else {
      Serial.println("Connection failed.");
      retryCount++;
      
      if (retryCount > 3) {
        retryCount = 0;
        Serial.println("Trying to Reconnect..");
      }
    }
  }
  
  while (1); // Infinite loop to halt further execution
}


