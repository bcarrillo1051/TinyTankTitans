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
#include "main.h"
#include "motors.h"



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
      motor = state_check_2D();     // Check next state of FSM
      break;
     // FORWARD State
      case ST_FORWARD:
      analogWrite(IN1,PWM_MOVE); // Motor on
      analogWrite(IN3,PWM_MOVE); // Motor on
      analogWrite(IN2,PWM_STOP); // Motor off
      analogWrite(IN4,PWM_STOP); // Motor off
      motor = state_check_2D();     // Check next state of FSM
      break;
     // BACKWARD State
      case ST_BACKWARD:
      analogWrite(IN2,PWM_MOVE); // Motor on
      analogWrite(IN4,PWM_MOVE); // Motor on
      analogWrite(IN1,PWM_STOP); // Motor off
      analogWrite(IN3,PWM_STOP); // Motor off
      motor = state_check_2D();     // Check next state of FSM
      break;
     // LEFT State
      case ST_LEFT:
      analogWrite(IN1,PWM_MOVE); // Motor on
      analogWrite(IN4,PWM_MOVE); // Motor on
      analogWrite(IN2,PWM_STOP); // Motor off
      analogWrite(IN3,PWM_STOP); // Motor off
      motor = state_check_2D();     // Check next state of FSM
      break;
     // RIGHT State
      case ST_RIGHT:
      analogWrite(IN2,PWM_MOVE); // Motor on
      analogWrite(IN3,PWM_MOVE); // Motor on
      analogWrite(IN1,PWM_STOP); // Motor off
      analogWrite(IN4,PWM_STOP); // Motor off
      motor = state_check_2D();     // Check next state of FSM
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
    // Creating an object of Servo class
  Servo myElevation;
  // Assigning GPIO ELEVATION to created object
  myElevation.attach(ELEVATION);
  // Counter for elevation
  int el = 0;
  while(true) { // Infinite Loop
    // Initial Position of Barrel
    myElevation.write(el);
    switch(barrel){ // Switch-Case for states
      // Idle State
      case ST_IDLE:
      barrel = state_check_Barrel();  // Check next state of FSM
      break;
      // Down State
      case ST_DOWN:
      if (el > MIN_ANGLE) {   // Have we reach minimum elevation yet?
        el -= ANGLE_INCREMENT;    // No, so then move it down
        myElevation.write(el);    // Update barrel
      }
      barrel = state_check_Barrel();  // Check next state of FSM
      break;
      // Up State
      case ST_UP:
      if (el < MAX_ANGLE) {   // Have we reach maximum elevation yet?
        el += ANGLE_INCREMENT;    // No, so then move it up
        myElevation.write(el);// Update barrel
      }
      barrel = state_check_Turret();  // Check next state of FSM
      break;
    } // End of switch-case statement
    // Task Delay by 
    vTaskDelay(DELAY_M);
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
  // Defining State Variable of FSM
  state_type turret = ST_IDLE;
  // Creating an object of Servo class
  Servo myAzimuth;
  // Assigning GPIO AZIMUTH to created object
  myAzimuth.attach(AZIMUTH);
  // Counter for azimuth
  int az = 0;
  while(true) { // Infinite Loop
    // Initial Position of Turret
    myAzimuth.write(az);
    switch(turret){ // Switch-Case for states
      // Idle State
      case ST_IDLE:
      turret = state_check_Turret();  // Check next state of FSM
      break;
      // Counter Clockwise State
      case ST_CCW:
      if (az > MIN_ANGLE) {   // Have we reach minimum azimuth yet?
        az -= ANGLE_INCREMENT;// No, so then rotate ccw
        myAzimuth.write(az);  // Update azimuthal motor
      }
      turret = state_check_Turret();  // Check next state of FSM
      break;
      //Clockwise State
      case ST_CW:
      if (az < MAX_ANGLE) {   // Have we reach maximum azimuth yet?
        az += ANGLE_INCREMENT;// No, so then rotate cw
        myAzimuth.write(az);  // Update azimuthal motor
      }
      turret = state_check_Turret();  // Check next state of FSM
      break;
    } // End of switch-case statement
    // Task Delay by 
    vTaskDelay(DELAY_M);
  } // End of while-loop
} // End of task_debounce function


/** @brief   This function returns the state for the movement motors.
 *  @details This function reads the current value of the share variable "movement"
 *           and returns the corresponding state value.
 *           This is used for the movement FSM state variable.
 * 
 *  @return  The state variable for movement FSM   
 */
state_type state_check_2D() {
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


/** @brief   This function returns the state for the turret motor.
 *  @details This function reads the current value of the share variable "angle_turret"
 *           and returns the corresponding state value.
 *           This is used for turret FSM state variable.
 * 
 *  @return  The state variable for turret FSM   
 */
state_type state_check_Turret() {
  // Right Button on App was pressed
  if(angle_turret.get()== 1)
    return ST_CW;
  // Left Button on App was pressed
  else if(angle_turret.get()== 2)
    return ST_CCW;
  // None of the barrel/turret control buttons on App were pressed
  else
    return ST_IDLE;
}


/** @brief   This function returns the state for the barrel motors.
 *  @details This function reads the current value of the share variable "angle_barrel"
 *           and returns the corresponding state value.
 *           This is used for barrel FSM state variable.
 * 
 *  @return  The state variable for barrel FSM   
 */
state_type state_check_Barrel() {
  // Up Button on App was pressed
  if(angle_barrel.get()== 1)
    return ST_UP;
  // Down Button on App was pressed
  else if(angle_barrel.get()== 2)
    return ST_DOWN;
  // None of the barrel/turret control buttons on App were pressed
  else
    return ST_IDLE;
}