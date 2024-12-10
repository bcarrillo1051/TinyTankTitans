/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file IR.h
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for defining shared variables
 * 
 * This file contains the definition of shared variables used for the tank projet.
 * These variables account for the features the user can control via bluetooth:
 * Tank 2D motion, barrel and turret angle, and IR data shooting.
 */

#include <taskshare.h>
#include <Arduino.h>

/*-----------------SHARED VARIABLES DEFINITIONS-------------------------- */
extern Share<uint16_t> movement;
extern Share<bool> fire;
extern Share<uint16_t> angle_barrel;
extern Share<uint16_t> angle_turret;
