/**
 * @file I2CSignalHandler.cpp
 * @brief Handles I2C communication signals and maps them to internal control flags.
 *
 * This module listens for specific I2C signals sent from a master device
 * and sets flags based on the received command. These flags can then be
 * queried from other parts of the program to perform corresponding actions.
 *
 * Signal Mapping:
 * - 'F' : Unlocks the system.
 * - 'C' : Lock the motor mechanism.
 * - 'S' : Bypass the authentication process.
 *
 * @author Alfonso Rodríguez.
 * @date 2025-04-23
 */

#include "I2CSignalHandler.h"

volatile SignalType lastSignal = NONE; ///< Stores the last received signal

/**
 * @brief Callback function triggered when data is received over I2C.
 *
 * This function reads incoming characters from the I2C buffer and
 * updates the internal signal flag accordingly.
 */
void receiveI2CSignal() {
  while (Wire.available()) {
    char receivedChar = Wire.read();
    if (receivedChar == 'F') {
      lastSignal = PASSWORD_RESET;
    } 
    else if (receivedChar == 'C') {
      lastSignal = MOTOR_LOCK_CLOSE;
    }
    else if (receivedChar == 'S') {
      lastSignal = SKIP;
    }
  }
}

/**
 * @brief Initializes I2C as a slave and registers the receive callback.
 */
void setupSignalHandler() {
  Wire.begin(8);  // Slave with direction 8.
  Wire.onReceive(receiveI2CSignal);
}

/**
 * @brief Checks if a password reset was requested via I2C.
 * @return true if a password reset signal was received
 */
bool isPasswordResetRequested() {
  return lastSignal == PASSWORD_RESET;
}

/**
 * @brief Checks if the motor lock should be closed based on I2C signal.
 * @return true if a motor lock close signal was received
 */
bool isMotorLockCloseRequested() {
  return lastSignal == MOTOR_LOCK_CLOSE;
}

/**
 * @brief Checks if authentication should be skipped.
 * @return true if a skip authentication signal was received
 */
bool skipAuthentication() {
  return lastSignal == SKIP;
}

/**
 * @brief Clears the current signal flag (sets it to NONE).
 */
void clearSignalFlag() {
  lastSignal = NONE;
}