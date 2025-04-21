/**
 * @file RemoteControl.ino
 * @brief Arduino sketch for receiving IR signals and controlling a fan system via serial and IR input.
 *
 * This sketch uses the IRremote library to receive signals from an infrared remote control.
 * It is designed to interface with a fan control system that operates automatically or via manual override.
 * Depending on the IR code received, the system can turn the fan on manually, off manually, or remain under automatic control.
 *
 * @details
 * - Uses an IR receiver module connected to digital pin 2.
 * - Periodically checks for IR signals and temperature/humidity data using TaskScheduler.
 * - Handles specific IR codes:
 *   - Code 22 (Button '0'): Unlocks the system by sending the character 'R' to the receiver Arduino.
 *   - Code 12 (Button '1'): Bypass the authentication process by sending the character 'O' to the receiver Arduino.
 *   - Code 21 (Button '+'): Activates the fan manually.
 * - Designed for use in a system with serial communication with 2 Arduino setups.
 * - Integrates with a DHT11 sensor and fan controller defined in `TemperatureFanController.h`.
 *
 * @note Initially, the fan was supposed to be turned off using the IR switch; however, due to electrical interference caused by the fan's DC motor 
 * when it is turned on, the IR signals are not read, so the proposed solution is to turn the fan off with a button.
 * @author Alfonso Rodríguez.
 * @date 2025-04-19
 */

#include <TaskScheduler.h>
#include <IRremote.h>
#include "TemperatureFanController.h"

// === IR setup ===
const int RECEPTOR_IR_PIN = 2;
IRrecv irrecv(RECEPTOR_IR_PIN); // IR receiver object instance.

// === Scheduler & Tasks ===
Scheduler runner;

void checkIR();             // Forward declaration
void readTempAndControl();  // Forward declaration

Task taskIR(50, TASK_FOREVER, &checkIR);               // Check IR every 50ms
Task taskTemp(2000, TASK_FOREVER, &readTempAndControl); // Every 2 sec

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Initialize the IR receiver.
  setupTemperatureFan(); // Initialize DHT and fan
  runner.init(); // Initialize the tasker.
  runner.addTask(taskIR); // Add the IR to the tasks queue.
  runner.addTask(taskTemp); // Add the TemperatureFanController operations to the tasks queue.
  taskIR.enable();
  taskTemp.enable();
}

void loop() {
  runner.execute();  // Run scheduled tasks.
}

/**
 * @brief Checks for IR input and handles fan control based on received codes.
 *
 * This function is called periodically, and managed certain operations with the IR set.
 * It reads the followings IR codes:
 * - If code 22 it will send the 'R' character via serial communication to the receiver Arduino, which will unlock the system.
 * - If code 12 is received, the fan is manually turned ON.
 * - If code 21 it will send the 'O' character via serial communciation to the receiver Arduino, which wll skip the authentication process.
 *
 * @note As mentioned above, turnOffFan() is a method that manages turning off the fan with the activation of a button. 
 * This method is part of the TemperatureFanController file.
 */
void checkIR() {
  turnOffFan(); // If the button is pressed, the fan will turn off.
  if (irrecv.decode()) {
    unsigned long value = irrecv.decodedIRData.command;  // Obtain the IR code, and transform it into a decimal format.
    Serial.print("Code: ");
    Serial.println(value);

    if (value == 22) {
      Serial.println("Boton 0");
      //Serial.write("R");  // Unlocks the system.
    }
    else if (value == 12) {
      Serial.println("Boton 1");
      //Serial.write("A"); // Skip the authentication process.
    }
    else if (value == 21) {
      Serial.println("Boton +");
      turnOnFan();
      //Serial.write("D");
    }
    irrecv.resume();  // Resume listening for the next IR signal.
  }
}

/**
 * @brief Reads temperature and humidity, and updates fan state accordingly.
 *
 * This function is called every 2 seconds to:
 * - Read temperature and humidity from the DHT11 sensor.
 * - Print the readings to the Serial monitor.
 * - Automatically turn the fan ON/OFF based on temperature threshold, unless a manual override is active.
 *
 * @see TemperatureFanController
 */
void readTempAndControl() {
  updateTemperatureFan();
}