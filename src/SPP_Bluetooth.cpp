/**
 * @file SPP_Bluetooth.cpp
 * @author Bryan Carrillo, Edgar Mora, Kerr Allen
 * @brief Makes use of the bluetooth capability for ESP32 (bluetooth server) 
 *        and processes received data from phones (bluetooth client) 
 * @version 0.1
 * @date 2024-12-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h> // Include the Arduino library for basic functionalities
#include "BluetoothSerial.h" // Include the BluetoothSerial library for Bluetooth communication

// Check if Bluetooth is properly enabled on ESP32
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT; // Create an instance of the BluetoothSerial class

const int ledPin = 2; // Define the GPIO pin number for the LED

void setup_2() {
  Serial.begin(115200); // Establish a connection between ESP32 and computer via USB, allows for printing
  SerialBT.begin("ESP32-BT"); // Initialize ESP32 BT capability, name provided is how it appears as a BT device
  //Serial.println("Device is ready for blueooth pairing!");
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop_2() {

  //Serial.println("Device is ready for blueooth pairing!");
  delay(2000);

  if (SerialBT.available()) { // Check if there are bytes of received data in the BT serial port
    char c = SerialBT.read(); // Read one character from the Bluetooth serial connection

    // Check if the turrent IR button has been pressed represented by a '1'
    if (c == '1') {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }


    // elif (54 < c < 104){
    //   right
    // }
    // elif (104 < c < 154){
    //   up
    // }
    // elif (4 < c < 54){
    //   left
    // }
    // elif (-54 < c < 4){
    //   down
    // }
    // Else dont send anything

  }
}
