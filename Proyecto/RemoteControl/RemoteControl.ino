/**
 * @file RemoteControl.ino
 * @brief Main controller for IR signal handling, temperature monitoring, and I2C communication.
 *
 * This sketch uses IR remote signals to control different functionalities,
 * such as toggling a fan, unlocking a system via I2C, and bypassing authentication.
 * It also periodically reads temperature values and controls a fan accordingly.
 *
 * @author 
 * Alfonso Rodríguez.
 * @date 2025-04-23
 */

#include <TaskScheduler.h>
#include <IRremote.h>
#include <Wire.h>
#include "TemperatureFanController.h"

// === IR setup ===
const int RECEPTOR_IR_PIN = 2;
IRrecv irrecv(RECEPTOR_IR_PIN); // IR receiver object instance.

// === I2C setup ===
const byte RECEPTOR_I2C_ADDRESS = 8;

// === Scheduler & Tasks ===
Scheduler runner;

void checkIR();             // Forward declaration
void readTempAndControl();  // Forward declaration

Task taskIR(50, TASK_FOREVER, &checkIR);               // Check IR every 50ms
Task taskTemp(2000, TASK_FOREVER, &readTempAndControl); // Every 2 sec

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Initialize the I2C as a Master.
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
 * @brief Checks for incoming IR signals and acts accordingly.
 * 
 * IR Remote Commands:
 * - Command 22: Sends 'F' via I2C to unlock system.
 * - Command 12: Sends 'C' via I2C to close motor lock.
 * - Command 24: Sends 'S' via I2C to skip authentication.
 * - Command 21: Turns the fan ON manually.
 */
void checkIR() {
  turnOffFan(); // If the button is pressed, the fan will turn off.
  if (irrecv.decode()) {
    unsigned long value = irrecv.decodedIRData.command;
    Serial.println(value);

    if (value == 22) { // Button: '0'
      Wire.beginTransmission(RECEPTOR_I2C_ADDRESS);
      Wire.write('F');  // Unlock the system.
      Wire.endTransmission();
    }
    else if (value == 12) { // Button: '1'
      Wire.beginTransmission(RECEPTOR_I2C_ADDRESS);
      Wire.write('C');  // Close the Motor.
      Wire.endTransmission();
    }
    else if (value == 24) { // Button: '2'
      Wire.beginTransmission(RECEPTOR_I2C_ADDRESS);
      Wire.write('S');  // Skip Authentication.
      Wire.endTransmission();
    }
    else if (value == 21) { // Button: '+'
      turnOnFan();  // Fan ON manually
    }
    irrecv.resume();  // Resume listening for the next IR signal.
  }
}

/**
 * @brief Reads temperature and controls the fan based on thresholds.
 * 
 * @see TemperatureFanController module.
 */
void readTempAndControl() {
  updateTemperatureFan();
}