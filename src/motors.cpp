/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file motors.cpp
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for DC and Servo Motors functions used for Tank project
 * 
 * @details
 * 
 */
#include "motors.h"


/** @brief   Task outputs a 250 Hz SquareWave on Pin 12.
 *  @details This task outputs a 250 Hz, 50% Duty Cycle on GPIO 12 of
 *           ESP32 Microcontroller. Square wave will be generated iff the inter-task shared variable
 *           "hide" is False; otherwise, if hide is true, the square wave won’t be shown,
 *           and the pin will sit at logic zero.
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_movement(void* p_param){

  // Defining Starting State of FSM
  state_type motor = ST_IDLE;

  while(true) { // Infinite Loop

    switch(motor){ // Switch-Case for states
      case ST_IDLE:
      analogWrite(IN2,PWM_STOP);
      analogWrite(IN4,PWM_STOP);
      analogWrite(IN1,PWM_STOP);
      analogWrite(IN3,PWM_STOP);
      delay(1000);
      motor = ST_FORWARD;
      break;

      case ST_FORWARD:
      analogWrite(IN1,PWM_MOVE);
      analogWrite(IN3,PWM_MOVE);
      analogWrite(IN2,PWM_STOP);
      analogWrite(IN4,PWM_STOP);
      delay(1000);
      motor = ST_BACKWARD;
      break;

      case ST_BACKWARD:
      analogWrite(IN2,PWM_MOVE);
      analogWrite(IN4,PWM_MOVE);
      analogWrite(IN1,PWM_STOP);
      analogWrite(IN3,PWM_STOP);
      delay(1000);
      motor = ST_LEFT;
      break;

      case ST_LEFT:
      analogWrite(IN1,PWM_MOVE);
      analogWrite(IN4,PWM_MOVE);
      analogWrite(IN2,PWM_STOP);
      analogWrite(IN3,PWM_STOP);
      delay(1000);
      motor = ST_RIGHT;
      break;

      case ST_RIGHT:
      analogWrite(IN2,PWM_MOVE);
      analogWrite(IN3,PWM_MOVE);
      analogWrite(IN1,PWM_STOP);
      analogWrite(IN4,PWM_STOP);
      delay(1000);
      motor = ST_IDLE;
      break;

    } // End of switch-case statement
    // Task Delay by 
    vTaskDelay(DELAY_M);
  } // End of while-loop
} // End of task_debounce function


/** @brief   Task outputs a 250 Hz SquareWave on Pin 12.
 *  @details This task outputs a 250 Hz, 50% Duty Cycle on GPIO 12 of
 *           ESP32 Microcontroller. Square wave will be generated iff the inter-task shared variable
 *           "hide" is False; otherwise, if hide is true, the square wave won’t be shown,
 *           and the pin will sit at logic zero.
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_barrel(void* p_param){
  // Defining Starting State of FSM
  state_type barrel = ST_IDLE;
  Servo myElevation;
  myElevation.attach(ELEVATION);
  int el = 0;
  while(true) { // Infinite Loop

    switch(barrel){ // Switch-Case for states
      case ST_IDLE:

      barrel = ST_UP;
      break;

      case ST_UP:
      for (el = 0; el <= 180; el += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myElevation.write(el);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      barrel = ST_DOWN;
      break;

      case ST_DOWN:
      for (el = 180; el >= 0; el -= 1) { // goes from 270 degrees to 0 degrees
        myElevation.write(el);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      barrel = ST_IDLE;
      break;
    } // End of switch-case statement
    // Task Delay by 
    vTaskDelay(DELAY_S);
  } // End of while-loop
} // End of task_debounce function


/** @brief   Task outputs a 250 Hz SquareWave on Pin 12.
 *  @details This task outputs a 250 Hz, 50% Duty Cycle on GPIO 12 of
 *           ESP32 Microcontroller. Square wave will be generated iff the inter-task shared variable
 *           "hide" is False; otherwise, if hide is true, the square wave won’t be shown,
 *           and the pin will sit at logic zero.
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_turret(void* p_param){
  // Defining Starting State of FSM
  state_type turret = ST_IDLE;
  Servo myAzimuth;
  myAzimuth.attach(AZIMUTH);
  int az = 0;
  while(true) { // Infinite Loop

    switch(turret){ // Switch-Case for states
      case ST_IDLE:

      turret = ST_CCW;
      break;

      case ST_CCW:
      for (az = 0; az <= 180; az += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myAzimuth.write(az);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      turret = ST_CW;
      break;

      case ST_CW:
      for (az = 180; az >= 0; az -= 1) { // goes from 270 degrees to 0 degrees
        myAzimuth.write(az);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      turret = ST_IDLE;
      break;
    } // End of switch-case statement
    // Task Delay by 
    vTaskDelay(DELAY_S);
  } // End of while-loop
} // End of task_debounce function