/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file motors.h
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for DC and Servo Motors definitions used for Tank project
 * 
 * This file is the main
 * 
 */
/*-----------------INCLUDE---------------------------------------- */
#include <Arduino.h>
#include <ESP32_Servo.h>
#include <taskshare.h>

/*-----------------CONSTANT DEFINITIONS--------------------------- */
#define ELEVATION   25
#define AZIMUTH     15
#define IN1         12
#define IN2         14
#define IN3         16
#define IN4          4
#define PWM_MOVE    70
#define PWM_STOP     0
#define DELAY_M    100
#define DELAY_S    100

// Defining a new type called state_type.
// Will be used to define the states for FSM
enum state_type {ST_IDLE, ST_FORWARD, ST_BACKWARD, ST_RIGHT, ST_LEFT,
                 ST_UP, ST_DOWN, ST_CW, ST_CCW};

/*-----------------FUNCTION DECLARATIONS-------------------------- */
void task_movement(void* p_param);
void task_barrel(void* p_param);
void task_turret(void* p_param);
state_type state_check(void);
