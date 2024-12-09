/** 
 * Copyright (C) 2024 by Tiny Tank Titans
 * @file IR.cpp
 * @authors Edgar Mora, Bryan Carrillo, Kerr Allan 
 * @date December/10/2024
 * @brief File for IR Receiver and Transmitter functions used for Tank project
 * 
 * This file is the main
 * 
 */
#include "IR.h"


void task_transmitter(void* p_param) {
    IRsend irTransmitter(IR_TRANSMITTER_PIN);
    irTransmitter.begin();
    // Example: Transmitting a Sony TV power on/off code
    //nsigned int sonyPowerCode[] = {0x55555555, 32};
    while(true) {

        // Here if statement checking for shared variable == FIRE BUTTON
        // If true, then send the data
        // otherwise just jump to vDelaytask
        irTransmitter.sendNEC(data); // ONLY if TRUE
  
        vTaskDelay(50);
    }
}

/**
 * @brief Task for receiving and processing IR (infrared) signals.
 * 
 * This function initializes an IR receiver and continuously checks for decoded IR signals. 
 * Upon receiving a signal, it verifies the signal value using a user-defined function 
 * and resumes the receiver for further signal detection.
 * 
 * @param p_param Pointer to the parameter passed to the task (unused in this implementation).
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