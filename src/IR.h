/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file IR.h
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for IR Receiver and Transmitter definitions used for Tank project
 * 
 * This file defines the constants, function prototypes, and include files used for the IR devices
 * used in the Tanks project.
 * 
 */
/*--------------------------------INCLUDE----------------------------------- */
#include <Arduino.h>
#include "main.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <assert.h>
#include <IRac.h>
#include <IRtext.h>

/*--------------------------CONSTANT DEFINITIONS---------------------------- */
#define IR_RECEIVER_PIN     21
#define IR_TRANSMITTER_PIN  22
#define LASER               23
#define LED                 19
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 40;  // Milli-Seconds
const uint32_t data= 0x55555555;

/*--------------------------FUNCTION DECLARATIONS--------------------------- */
void task_receiver(void* p_param);
void task_transmitter(void* p_param);
void verify_signal(uint32_t signal_Data);