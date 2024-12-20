/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file main.cpp
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for fully operating Bluetooth-Controlled Tank
 * 
 * This file contains the main functions for the Tank Project. It contains the definition of shared variables
 * used for bluetooth interaction with the tank.
 * The setup and loop functions are also defined in here.
 * 
 */
#include "main.h"
#include "motors.h"
#include "IR.h"
#include "bluetooth.h"

// Share variables used for the three different actions the user can do on the App
Share<uint16_t> movement ("Tank 2D Movement");          // Used for 2D motion
Share<bool> fire ("Tank Firing");                       // Used for Firing "IR bullet"
Share<uint16_t> angle_turret ("Tank Turret Movement");  // Used for Turret motion
Share<uint16_t> angle_barrel ("Tank Barrel Movement");  // Used for Barrel motion


/** @brief   Initializes all the GPIOS, variables and tasks.
 *  @details This function sets up all the GPIOS used for the tank as inputs/outputs.
 *           It also initializes the shared task variables, and the different tasks implemented.
 */
void setup() {
  
  setup_SPP_Bluetooth(); 

  pinMode(ELEVATION,OUTPUT);
  pinMode(AZIMUTH,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(LASER,OUTPUT);
  // Aiming Laser is always ON
  digitalWrite(LASER,HIGH);
  // Initializing PWM of 2D movement motors to 0
  analogWrite(IN1,PWM_STOP);
  analogWrite(IN2,PWM_STOP);
  analogWrite(IN3,PWM_STOP);
  analogWrite(IN4,PWM_STOP);
  // Creating the different tasks associated with the project
  xTaskCreate (task_turret, "Tank Turret Motion", 2048, NULL, 1, NULL);
  xTaskCreate (task_barrel, "Tank Barrel Motion", 2048, NULL, 2, NULL);
  xTaskCreate (task_movement, "Tank 2D Motion", 2048, NULL, 3, NULL);
  xTaskCreate (task_receiver, "Tank IR Receiver", 2048, NULL, 4, NULL);
  xTaskCreate (task_transmitter, "Tank IR Transmitter", 2048, NULL, 5, NULL); 
  xTaskCreate (task_bluetooth, "Bluetooth Communication", 2048, NULL, 6, NULL);
}


/** @brief   Function that runs forever.
 *  @details This function executes in a loop indefinitely.
 */
void loop() {
  // RUN FORREST...RUUUUUUUUUUUUN!
}
