/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file IR.cpp
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for IR Receiver and Transmitter functions used for Tank project
 * 
 * This file contains all the funcions and tasks related to both IR Transmitter and Receiver devices.
 * These tasks include transmission and reception of IR data to/from another tank.
 */
#include "main.h"
#include "IR.h"


/** @brief   Task transmits IR data
 *  @details This task transmits IR data through the tank's barrel based on the shared variable "fire"
 *           controlled by the phone-based app.
 * 
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_transmitter(void* p_param) {
    // Creates an object of the class IRsend
    IRsend irTransmitter(IR_TRANSMITTER_PIN);
    // Initializes IR transmission 
    irTransmitter.begin();
    // Example: Transmitting a Sony TV power on/off code
    //nsigned int sonyPowerCode[] = {0x55555555, 32};
    while(true) {
        if(fire.get())  // Was the fire button pressed?
            irTransmitter.sendNEC(data); // Yes, then shoot "IR bullet"
        vTaskDelay(50); // Delay for 50ms before shooting again
    }
}

/**
 * @brief   Task for receiving and processing IR (infrared) signals.
 * 
 * @details This function initializes an IR receiver and continuously checks for decoded IR signals. 
 *          Upon receiving a signal, it verifies the signal value using a user-defined function 
 *          and resumes the receiver for further signal detection.
 * 
 * @param   p_params A pointer to parameters passed to this task. This 
 *          pointer is ignored; it should be set to @c NULL in the 
 *          call to @c xTaskCreate() which starts this task
 */
void task_receiver(void* p_param) {
    // Initialize the IR receiver object with specified parameters:
    // - IR_RECEIVER_PIN: Pin where the IR receiver module is connected.
    // - kCaptureBufferSize: Size of the buffer for capturing IR signals.
    // - kTimeout: Duration to wait for an IR signal before timing out.
    // - false: Disable the repeat signal detection flag.
    IRrecv irReceiver(IR_RECEIVER_PIN, kCaptureBufferSize, kTimeout, false);
    // Create a decode_results object to hold the decoded IR signal data.
    decode_results irResults;
    // Initialize the IR transmitter object on the specified pin.
    IRsend irTransmitter(IR_TRANSMITTER_PIN);
    // Enable the IR receiver module to start capturing signals.
    irReceiver.enableIRIn();
    // Start an infinite loop to continuously monitor IR signals.
    while (true) {
        // Check if an IR signal has been successfully decoded.
        if (irReceiver.decode(&irResults)) {
            // Process the decoded signal by passing its value to the verify_signal function.
            verify_signal(irResults.value);
            // Prepare the receiver to resume capturing the next signal.
            irReceiver.resume();
        }
        // Add a delay of 200 milliseconds before the next iteration to avoid
        // rapid polling and conserve CPU resources.
        vTaskDelay(200);
    }
}


/** @brief   This function determines if the tank was succesfully shot.
 *  @details This function attempts to read data sent to the IR receiver.
 *           If the data that represents a bullet shot is received, then
 *           an LED light is turned ON for 1 second to report shooting
 * 
 *  @param  signal_Data Current IR data read by receiver.   
 */
void verify_signal(uint32_t signal_Data) {
  // Has the tank being shot?
  if (signal_Data == data) {
    // Yes,Turn ON Flag LED to notify user
    digitalWrite(LED,HIGH);
    // Keep the Flag LED ON for 1 second
    delay(1000);
    // Turn OFF LED
    digitalWrite(LED,LOW);
  } // end of if-statement
}