/**
 * @file IRReceiver.ino
 * @brief Arduino sketch for receiving IR signals and forwarding a command via serial communication.
 *
 * This sketch uses the IRremote library to receive signals from an infrared remote control.
 * When a specific IR code (e.g., button '0') is detected, it sends a character via serial 
 * to another Arduino acting as the receiver.
 *
 * @details
 * - Uses an IR receiver module connected to digital pin 2.
 * - Prints the received IR codes to the serial monitor.
 * - Sends the character 'R' through the serial port when code 22 is received.
 * - Designed to be used in a two-Arduino system using serial communication.
 *
 * @author Alfonso Rodríguez.
 * @date 2025-04-19
 */

#include <IRremote.h>

const int RECEPTOR_IR_PIN = 2;
IRrecv irrecv(RECEPTOR_IR_PIN); // IR receiver object instance.

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Initialize the IR receiver.
}

void loop() {
  if (irrecv.decode()) {
    unsigned long value = irrecv.decodedIRData.command;  // Obtain the IR code.
    Serial.print("Code: ");
    Serial.println(value);

    if (value == 22) {  // Value associated with the '0' button.
      Serial.write("R");  // Send 'R' to the other Arduino via Serial Communication.
    }
    irrecv.resume();  // Resume listening for the next IR signal.
  }
}