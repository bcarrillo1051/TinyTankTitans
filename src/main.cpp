/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file main.cpp
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for fully operating Bluetooth-Controlled Tank
 * 
 * This file is the main
 * 
 */
#include "motors.h"
#include "IR.h"
#include "main.h"

// Share variable, Determines if Square Wave will be generated or not
Share<uint16_t> movement ("Tank 2D Movement");
Share<bool> fire ("Tank Firing");
Share<uint16_t> angles ("Tank Turret and Barrel Movement");

void setup() {
  
  pinMode(ELEVATION,OUTPUT);
  pinMode(AZIMUTH,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(LASER,OUTPUT);

  digitalWrite(LASER,HIGH);

  analogWrite(IN1,PWM_STOP);
  analogWrite(IN2,PWM_STOP);
  analogWrite(IN3,PWM_STOP);
  analogWrite(IN4,PWM_STOP);

  xTaskCreate (task_movement, "Tank 2D Motion", 2048, NULL, 7, NULL);
  xTaskCreate (task_barrel, "Tank Barrel Motion", 2048, NULL, 6, NULL);
  xTaskCreate (task_turret, "Tank Turret Motion", 2048, NULL, 5, NULL);
  xTaskCreate (task_receiver, "Tank Receiver ", 2048, NULL, 8, NULL); 
}

void loop() {
  // put your main code here, to run repeatedly:
}
