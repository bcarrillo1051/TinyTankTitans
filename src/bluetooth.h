/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file bluetooth.h
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for bluetooth definitions used for Tank project
 * 
 * This file is the main
 * 
 */

/*-----------------INCLUDE---------------------------------------- */
#include <Arduino.h> // Include the Arduino library for basic functionalities
#include "BluetoothSerial.h" // Include the BluetoothSerial library for Bluetooth communication

/*--------------------------MACROS---------------------------- */
// Check if Bluetooth is properly enabled on ESP32
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

// Analog Stick bound defitions
#define LEFT_LOWER_BOUND_X 4
#define LEFT_UPPER_BOUND_X 34
#define RIGHT_LOWER_BOUND_X 74
#define RIGHT_UPPER_BOUND_X 104
#define DOWN_LOWER_BOUND_X 34
#define DOWN_UPPER_BOUND_X 74
#define UP_LOWER_BOUND_X 34
#define UP_UPPER_BOUND_X 74

#define LEFT_LOWER_BOUND_Y 34
#define LEFT_UPPER_BOUND_Y 74
#define RIGHT_LOWER_BOUND_Y 34
#define RIGHT_UPPER_BOUND_Y 74
#define DOWN_LOWER_BOUND_Y 4
#define DOWN_UPPER_BOUND_Y 34
#define UP_LOWER_BOUND_Y 74
#define UP_UPPER_BOUND_Y 104

/*--------------------------FUNCTION DECLARATIONS--------------------------- */
void setup_SPP_Bluetooth(); 
void task_bluetooth(void* p_param);