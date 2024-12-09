/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file IR.h
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for IR Receiver and Transmitter definitions used for Tank project
 * 
 * This file is the main
 * 
 */

#include <taskshare.h>
#include <Arduino.h>

/*-----------------CONSTANTS DEFINITIONS-------------------------- */


// Share variable, Determines if Square Wave will be generated or not
extern Share<uint16_t> movement;
extern Share<bool> fire;
extern Share<uint16_t> angles;
