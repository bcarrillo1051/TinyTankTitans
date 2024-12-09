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


void task_receiver(void* p_param) {
        // Create an instance of the IR receiver with specified parameters
    // IR_RECEIVER_PIN: Pin where the IR receiver is connected
    // kCaptureBufferSize: Size of the capture buffer for decoding IR signals
    // kTimeout: Timeout for waiting to receive a signal
    // false: Do not use a repeat flag
    IRrecv irReceiver(IR_RECEIVER_PIN,kCaptureBufferSize,kTimeout,false);
    decode_results irResults;
    IRsend irTransmitter(IR_TRANSMITTER_PIN);
    irReceiver.enableIRIn();

  while(true) {
    if (irReceiver.decode(&irResults)) {
        verify_signal(irResults.value);
        irReceiver.resume();
    }
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