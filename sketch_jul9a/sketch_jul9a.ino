#include <SPI.h>
#include <WiFi101_Generic.h>
#include "secrets.h"

IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 100, 1);
IPAddress local_ip(192, 168, 100, 35);

int status = WL_IDLE_STATUS;
unsigned int localPort = 4000;
WiFiServer server(80);  // Corrected from WifiServer to WiFiServer

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  if (WiFi.status() == WL_NO_SHIELD) {  // Corrected from Wifi to WiFi
    Serial.println("Shield not present!");
    while (true); // don't continue
  }
  
  WiFi.config(local_ip, gateway, subnet); // Corrected the IP variable
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("place ssid name here:");  // You should replace this with your actual SSID
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);  // Corrected from Wifi to WiFi
    delay(10000);
  }
  
  server.begin();  // Corrected from server to WiFiServer instance
  Serial.println("Connected");
}

void loop() {
  // put your main code here, to run repeatedly:

}  

