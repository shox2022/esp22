#include <SoftwareSerial.h>

// Create a SoftwareSerial object to communicate with the Bluetooth module
SoftwareSerial Bluetooth(10, 11); // RX, TX

void setup() {
  // Start the hardware serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Start the software serial communication at a baud rate of 9600
  Bluetooth.begin(9600);

  // Print a message to the serial monitor
  Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
  // If data is available on the Bluetooth serial port
  if (Bluetooth.available()) {
    // Read the data and print it to the hardware serial port
    char data = Bluetooth.read();
    Serial.print(data);
  }

  // If data is available on the hardware serial port
  if (Serial.available()) {
    // Read the data and print it to the Bluetooth serial port
    char data = Serial.read();
    Bluetooth.print(data);
  }
}
