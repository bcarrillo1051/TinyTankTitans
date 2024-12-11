/**
 * @file SPP_Bluetooth.cpp
 * @author Bryan Carrillo, Edgar Mora, Kerr Allan
 * @brief Makes use of the bluetooth capability for ESP32 (bluetooth server) 
 *        and processes received data from phones (bluetooth client) 
 * @version 0.1
 * @date 2024-12-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "main.h"
#include "bluetooth.h"
#include<iostream>
#include<string.h>


// Global Variables
BluetoothSerial SerialBT; // Create an instance of the BluetoothSerial class
const int ledPin = 2; // Define the GPIO pin number for the LED


/** @brief   Function that initializes ESP32 bluetooth capability
 *  @details This function initializes the bluetooth capability of the ESP32 so that it can be a
 *           selectable device
 * 
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void setup_SPP_Bluetooth(){
  Serial.begin(115200); // Establish a connection between ESP32 and computer via USB, allows for printing
  SerialBT.begin("ESP32-BT"); // Initialize ESP32 BT capability, name provided is how it appears as a BT device
}


/** @brief   Task that set up bluetooth capability for Tank Project
 *  @details This task takes analog joystick data, as well as button data and maps it to a D-pad range
 * 
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_bluetooth(void* p_param){

  // D-Pad look up table based on x and y area that is detected
  // region: 0 = center, 1 = up, 2 = down, 3 = left, 4 = right
  int regionLookup[3][3] = {
      {DIAGONAL, UP, DIAGONAL},
      {LEFT, CENTER, RIGHT},
      {DIAGONAL, DOWN, DIAGONAL}
  };

  // x_area: 1 = center third, 2 = left third, 3 = right third
  uint16_t x_area = 1; // Default for center of ball
  // y_area: 1 = center third, 2 = down third, 3 = up third
  uint16_t y_area = 1; // Default for center of ball

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
        // Serial.println("Button Pressed!");
        // digitalWrite(ledPin, HIGH);
        // delay(1000);
        // digitalWrite(ledPin, LOW);
        // Serial.println();
        fire.put(1); // Shoot 
      }
      else {
        fire.put(0); // Don't shoot
      }

      // --- MOVEMENT X-AXIS CHECK (LEFT ANALOG STICK) ---
      if (c == 'x'){
        char xData = SerialBT.read();
        int dummy = (int)xData;
        Serial.print("Tank left/right movement (x) data: ");
        Serial.println(dummy);

        // Serial.print("Number of bytes in buffer (x): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();  

        if (LEFT_LOWER_BOUND_X < xData < LEFT_UPPER_BOUND_X){ // If x is in left button area
          x_area = 0;
        }
        else if (UP_DOWN_LOWER_BOUND_X < xData < UP_DOWN_UPPER_BOUND_X){ // If x is in up or bottom button area
          x_area = 1;
        }
        else if (RIGHT_LOWER_BOUND_X < xData < RIGHT_UPPER_BOUND_X){ // If x is in right button area
          x_area = 2;
        }  
  

      } 

      // --- MOVEMENT Y-AXIS CHECK (LEFT ANALOG STICK) ---
      if (c == 'y'){ // Movemement y-axis analog stick data
        char yData = SerialBT.read();
        int dummy = (int)yData;
        Serial.print("Tank forward/back movement (y) data: ");
        Serial.println(dummy); 

        // Serial.print("Number of bytes in buffer (y): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();  

        if (UP_LOWER_BOUND_Y < yData < UP_UPPER_BOUND_Y){ // If y is in up button area
          y_area = 0;
        }
        else if (LEFT_RIGHT_LOWER_BOUND_Y < yData < LEFT_RIGHT_UPPER_BOUND_Y){ // If y is in left or right button area
          y_area = 1;
        }
        else if (DOWN_LOWER_BOUND_Y < yData < DOWN_UPPER_BOUND_Y){ // If y is in down button area
          y_area = 2;
        }

        // Compute D-Pad region
        uint16_t region = regionLookup[y_area][x_area];

        if (region == UP){ // If x and y is center and up respectively
          movement.put(1);
        }
        else if (region == DOWN){ // If x and y is center and down respectively
          movement.put(2);
        }
        else if (region == LEFT){ // If x and y is left and center respectively
          movement.put(3);
        }
        else if (region == RIGHT){ // If x and y is right and center respectively
          movement.put(4);
        }
        else{ // If x and y is center and center respectively
          movement.put(0);
        }
      }

      // --- AZIMUTHAL X-AXIS CHECK (RIGHT ANALOG STICK) ---
      if (c == 'a'){
        char xData = SerialBT.read();
        int dummy = (int)xData;
        Serial.print("Tank azimuthal (x) data: ");
        Serial.println(dummy);
        // Serial.print("Number of bytes in buffer (x): ");  
        // Serial.println(SerialBT.available()); 
        // Serial.println();

        if (LEFT_LOWER_BOUND_X < xData < LEFT_UPPER_BOUND_X){ // If x is in left button area
          x_area = 0;
        }
        else if (UP_DOWN_LOWER_BOUND_X < xData < UP_DOWN_UPPER_BOUND_X){ // If x is in up or bottom button area
          x_area = 1;
        }
        else if (RIGHT_LOWER_BOUND_X < xData < RIGHT_UPPER_BOUND_X){ // If x is in right button area
          x_area = 2;
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
          y_area = 0;
        }
        else if (LEFT_RIGHT_LOWER_BOUND_Y < yData < LEFT_RIGHT_UPPER_BOUND_Y){ // If y is in left or right button area
          y_area = 1;
        }
        else if (DOWN_LOWER_BOUND_Y < yData < DOWN_UPPER_BOUND_Y){ // If y is in down button area
          y_area = 2;
        }

        // Compute D-Pad region
        uint16_t region = regionLookup[y_area][x_area];

        if (region == UP){ // If x and y is center and up respectively
          angle_barrel.put(1);
        }
        else if (region == DOWN){ // If x and y is center and down respectively
          angle_barrel.put(2);
        }
        else if (region == RIGHT){ // If x and y is right and center respectively
          angle_turret.put(1);
        }
        else if (region == LEFT){ // If x and y is left and center respectively
          angle_turret.put(2);
        }
        else{ // If x and y is center and center respectively
          angle_barrel.put(0);
          angle_turret.put(0);
        }
      }
    }
  vTaskDelay(100);
  }
}