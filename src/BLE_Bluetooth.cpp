#include <Arduino.h>
#include <BLEDevice.h>  // Core BLE library for ESP32
#include <BLEUtils.h>   // Utility functions for BLE
#include <BLEServer.h>  // BLE Server functionality

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

// UUIDs for the BLE Service and Characteristic
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // Unique ID for the BLE service
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // Unique ID for the BLE characteristic
#define ledPIN 2 // GPIO pin for the LED

// Custom callback class to handle BLE events when data is written to the characteristic
class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    // Get the value written to the characteristic
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0) { // Check if data is available
      Serial.println("*********");
      Serial.print("New value: ");
      
      for (int i = 0; i < value.length(); i++) { // Loop through received characters
        Serial.print(value[i]); // Print each character for debugging
        
        // Check the value and toggle the LED accordingly
        if (value[i] == '1') {
          digitalWrite(ledPIN, HIGH); // Turn LED ON
        } 
        if (value[i] == '0') {
          digitalWrite(ledPIN, LOW);  // Turn LED OFF
        }
      }

      Serial.println(); // Print a newline for better formatting
      Serial.println("*********");
    }
  }
};

void setup() {
  // Configure the LED pin as output
  pinMode(ledPIN, OUTPUT);

  // Start the Serial Monitor
  Serial.begin(115200);
  Serial.println("1- Download and install a BLE scanner app on your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to 'ESP32'");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- Observe the LED toggle =)");

  // Initialize BLE and set the device name
  BLEDevice::init("ESP32"); // Name of the BLE device
  BLEServer *pServer = BLEDevice::createServer(); // Create a BLE server

  // Create a new BLE service with the defined UUID
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE characteristic with defined UUID and properties (read and write)
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  // Attach the custom callback to handle writes to the characteristic
  pCharacteristic->setCallbacks(new MyCallbacks());

  // Set an initial value for the characteristic
  pCharacteristic->setValue("Hello World");

  // Start the BLE service
  pService->start();

  // Start advertising the BLE service so it can be discovered by clients
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {
  // Add a delay to reduce CPU usage, as BLE runs in the background
  delay(2000);
}
