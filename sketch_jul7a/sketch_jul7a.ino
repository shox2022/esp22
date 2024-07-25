#include <CMMC WiFiConnector.h>  // Include the CMMC WiFi Connector library

CMMC WiFiConnector connector;  // Create an instance of the connector

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud

  // Set up callback for when AP mode starts
  connector.setAPCallback([]() {
    Serial.println("AP started");
  });

  // Set up callback for when AP configuration is ready
  connector.setAPConfigCallback([]() {
    Serial.println("AP Config Ready");
  });

  // Set up callback for when WiFi is connected
  connector.setWifiCallback([](void) {
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
  });

  // Begin the WiFi connection with your SSID and password
  connector.begin("VODAFONE-5G", "kCPMAj7t");
}

void loop() {
  connector.loop();  // Call the loop function to handle WiFi connection logic
}


