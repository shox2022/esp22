#include <WiFi.h>

char ssid[] = "VODAFONE";
char pass[] = "kCPMAj7t";

int status = WL_IDLE_STATUS;

char server[] = "http://localhost/phpmyadmin/";

WiFiClient client;

void setup() {
  Serial.begin(9600);

  // Attempt to connect to Wi-Fi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  // Try to connect to the server
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    client.stop(); // Disconnect after the connection is established
  } else {
    Serial.println("Connection to server failed");
  }

  delay(3000); // Wait for 3 seconds before trying again
}


