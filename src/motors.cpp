/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file motors.cpp
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for DC and Servo Motors functions used for Tank project
 * 
 * @details This file contains all the fuctions related to the motors used in the tank project.
 *          Motors for this project are used to move the tank, its barrel, and its turret.
 * 
 */
#include "motors.h"
#include "main.h"


/** @brief   Task controls 2D motion of the Tank
 *  @details This task runs a FSM which controls the 2D motion of the tank.
 *           There are 5 possible states: Idle, Forward, Backwards, Left, Right.
 *           The state depends on the data sent via bluetooth.
 * 
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_movement(void* p_param){
  // Defining State variable of movement FSM
  state_type motor = ST_IDLE;

  while(true) { // Infinite Loop

    switch(motor){ // Switch-Case for states
      // IDLE State
      case ST_IDLE:
      analogWrite(IN2,PWM_STOP); // Motor off
      analogWrite(IN4,PWM_STOP); // Motor off
      analogWrite(IN1,PWM_STOP); // Motor off
      analogWrite(IN3,PWM_STOP); // Motor off
      motor = state_check();     // Check next state of FSM
      break;
     // FORWARD State
      case ST_FORWARD:
      analogWrite(IN1,PWM_MOVE); // Motor on
      analogWrite(IN3,PWM_MOVE); // Motor on
      analogWrite(IN2,PWM_STOP); // Motor off
      analogWrite(IN4,PWM_STOP); // Motor off
      motor = state_check();     // Check next state of FSM
      break;
     // BACKWARD State
      case ST_BACKWARD:
      analogWrite(IN2,PWM_MOVE); // Motor on
      analogWrite(IN4,PWM_MOVE); // Motor on
      analogWrite(IN1,PWM_STOP); // Motor off
      analogWrite(IN3,PWM_STOP); // Motor off
      motor = state_check();     // Check next state of FSM
      break;
     // LEFT State
      case ST_LEFT:
      analogWrite(IN1,PWM_MOVE); // Motor on
      analogWrite(IN4,PWM_MOVE); // Motor on
      analogWrite(IN2,PWM_STOP); // Motor off
      analogWrite(IN3,PWM_STOP); // Motor off
      motor = state_check();     // Check next state of FSM
      break;
     // RIGHT State
      case ST_RIGHT:
      analogWrite(IN2,PWM_MOVE); // Motor on
      analogWrite(IN3,PWM_MOVE); // Motor on
      analogWrite(IN1,PWM_STOP); // Motor off
      analogWrite(IN4,PWM_STOP); // Motor off
      motor = state_check();     // Check next state of FSM
      break;
    } // End of switch-case statement
    vTaskDelay(DELAY_M);         // Task Delay by 100 ms
  } // End of while-loop
} // End of task_debounce function


/** @brief   Task controls the Tank's Barrel.
 *  @details This task runs a FSM which controls the Barrel of the tank.
 *           There are 3 possible states: Idle, Up, and Down.
 *           The state depends on the data sent via bluetooth.
 * 
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


/** @brief   Task controls the Tank's Turret.
 *  @details This task runs a FSM which controls the Turret of the tank.
 *           There are 3 possible states: Idle, Clockwise (CW), and Counter-Clockwise (CCW).
 *           The state depends on the data sent via bluetooth.
 * 
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


/** @brief   This function returns the state for the movement motors.
 *  @details This function reads the current value of the share variable "movement"
 *           and returns the corresponding state value.
 *           This is used for the movement FSM state variable.
 * 
 *  @return  The state variable for movement FSM   
 */
state_type state_check() {
  // Up Button on App was pressed
  if(movement.get()== 1)
    return ST_FORWARD;
  // Down Button on App was pressed
  else if(movement.get()== 2)
    return ST_BACKWARD;
  // Left Button on App was pressed
  else if(movement.get()== 3)
    return ST_LEFT;
  // Right Button on App was pressed
  else if(movement.get()== 4)
    return ST_RIGHT;
  // None of the direction buttons on App were pressed
  else
    return ST_IDLE;
}