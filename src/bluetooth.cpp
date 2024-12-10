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

#include "bluetooth.h"
#include<iostream>
#include<string.h>

// Global Variables
BluetoothSerial SerialBT; // Create an instance of the BluetoothSerial class
const int ledPin = 2; // Define the GPIO pin number for the LED

void setup_SPP_Bluetooth(){
  Serial.begin(115200); // Establish a connection between ESP32 and computer via USB, allows for printing
  SerialBT.begin("ESP32-BT"); // Initialize ESP32 BT capability, name provided is how it appears as a BT device
  //Serial.println("Device is ready for blueooth pairing!");
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void task_bluetooth(void* p_param){
  while(true){

    if (SerialBT.available()){ // Check if there are bytes of received data
      // Serial.print("Number of bytes in buffer (Start): ");  
      // Serial.println(SerialBT.available()); 
      char c = SerialBT.read(); // Read the flag
      Serial.print("Flag Read: ");
      Serial.println(c);
      // Serial.print("Number of bytes in buffer (after reading flag): ");  
      // Serial.println(SerialBT.available()); 
      // Serial.println();
  
      // --- BUTTON PRESS CHECK ---
      if (c == 'b'){
        Serial.println("Button Pressed!");
        // digitalWrite(ledPin, HIGH);
        // delay(1000);
        // digitalWrite(ledPin, LOW);
        // Serial.println();
        // fire.put(1);
      }
      else {
        fire.put(0);
      }

      // --- MOVEMENT X-AXIS CHECK (LEFT ANALOG STICK) ---
      if (c == 'x'){
        char xData = SerialBT.read();
        int dummy = (int)xData;
        Serial.print("Tank left/right movement (x) data: ");
        Serial.println(dummy);

        if (UP_LOWER_BOUND_X < xData < UP_UPPER_BOUND_X){ // If x is in up button area
          movement.put(1);
        }
        else if (DOWN_LOWER_BOUND_X < xData < DOWN_UPPER_BOUND_X){ // If x is in down button area
          movement.put(2);
        }
        else if (LEFT_LOWER_BOUND_X < xData < LEFT_UPPER_BOUND_X){ // If x is in left button area
          movement.put(3);
        }
        else if (RIGHT_LOWER_BOUND_X < xData < RIGHT_UPPER_BOUND_X){ // If x is in right button area
          movement.put(4);
        }
        else{ // If x is at the center of the ball x ==5 4
          movement.put(0);
        }
        // Serial.print("Number of bytes in buffer (x): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();    
      } 

      // --- MOVEMENT Y-AXIS CHECK (LEFT ANALOG STICK) ---
      if (c == 'y'){ // Movmement y-axis analog stick data
        char yData = SerialBT.read();
        int dummy = (int)yData;
        Serial.print("Tank forward/back movement (y) data: ");
        Serial.println(dummy);
        // Serial.print("Number of bytes in buffer (y): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();   

        if (UP_LOWER_BOUND_Y < yData < UP_UPPER_BOUND_Y){ // If y is in up button area
          movement.put(1);
        }
        else if (DOWN_LOWER_BOUND_Y < yData < DOWN_UPPER_BOUND_Y){ // If y is in down button area
          movement.put(2);
        }
        else if (LEFT_LOWER_BOUND_Y < yData < LEFT_UPPER_BOUND_Y){ // If y is in left button area
          movement.put(3);
        }
        else if (RIGHT_LOWER_BOUND_Y < yData < RIGHT_UPPER_BOUND_Y){ // If y is in right button area
          movement.put(4);
        }
        else{ // If x is at the center of the ball x ==5 4
          movement.put(0);
        }

      }

      // --- MOVEMENT X-AXIS CHECK (RIGHT ANALOG STICK) ---
      if (c == 'a'){
        char xData = SerialBT.read();
        int dummy = (int)xData;
        Serial.print("Tank azimuthal (x) data: ");
        Serial.println(dummy);
        // Serial.print("Number of bytes in buffer (x): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();

        if (UP_LOWER_BOUND_X < xData < UP_UPPER_BOUND_X){ // If x is in up button area
          movement.put(1);
        }
        else if (DOWN_LOWER_BOUND_X < xData < DOWN_UPPER_BOUND_X){ // If x is in down button area
          movement.put(2);
        }
        else if (LEFT_LOWER_BOUND_X < xData < LEFT_UPPER_BOUND_X){ // If x is in left button area
          movement.put(3);
        }
        else if (RIGHT_LOWER_BOUND_X < xData < RIGHT_UPPER_BOUND_X){ // If x is in right button area
          movement.put(4);
        }
        else{ // If x is at the center of the ball x == 54
          movement.put(0);
        }

      } 

      // --- MOVEMENT Y-AXIS CHECK (RIGHT ANALOG STICK) ---
      if (c == 'e'){
        char yData = SerialBT.read();
        int dummy = (int)yData;
        Serial.print("Tank elevation (y) data: ");
        Serial.println(dummy);
        // Serial.print("Number of bytes in buffer (y): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();  

        if (UP_LOWER_BOUND_Y < yData < UP_UPPER_BOUND_Y){ // If y is in up button area
          movement.put(1);
        }
        else if (DOWN_LOWER_BOUND_Y < yData < DOWN_UPPER_BOUND_Y){ // If y is in down button area
          movement.put(2);
        }
        else if (LEFT_LOWER_BOUND_Y < yData < LEFT_UPPER_BOUND_Y){ // If y is in left button area
          movement.put(3);
        }
        else if (RIGHT_LOWER_BOUND_Y < yData < RIGHT_UPPER_BOUND_Y){ // If y is in right button area
          movement.put(4);
        }
        else{ // If x is at the center of the ball x == 54
          movement.put(0);
        }

      }
    }

  vTaskDelay(100);
  }
}

