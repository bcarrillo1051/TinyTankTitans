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
#include "motors.h"
#include "IR.h"
#include "main.h"

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
  // Initializing shared variables
  movement.put(0);
  fire.put(false);
  angle_turret.put(0);
  angle_barrel.put(0);
  // Initializing GPIO Pins as Inputs/Outputs
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
  xTaskCreate (task_movement, "Tank 2D Motion", 2048, NULL, 7, NULL);
  xTaskCreate (task_barrel, "Tank Barrel Motion", 2048, NULL, 6, NULL);
  xTaskCreate (task_turret, "Tank Turret Motion", 2048, NULL, 5, NULL);
  xTaskCreate (task_receiver, "Tank Receiver ", 2048, NULL, 8, NULL); 
}


/** @brief   Function that runs forever.
 *  @details This function executes in a loop indefinitely.
 */
void loop() {
  // RUN FORREST...RUUUUUUUUUUUUN!
}
