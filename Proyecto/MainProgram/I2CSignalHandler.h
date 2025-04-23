/**
 * @file I2CSignalHandler.h
 * @brief Header file for I2C signal handling on a slave device.
 *
 * Provides an interface to handle incoming I2C signals and map them to
 * high-level control commands. Used for inter-device communication,
 * typically between a master controller and a slave module that performs
 * security or mechanical actions.
 *
 * Signal Definitions:
 * - 'F' : Triggers a password reset
 * - 'C' : Closes a motor lock mechanism
 * - 'S' : Skips the authentication process
 * 
 * @author Alfonso Rodríguez.
 * @date 2025-04-23
 */

#ifndef I2C_SIGNAL_HANDLER_H
#define I2C_SIGNAL_HANDLER_H

#include <Wire.h>

/**
 * @enum SignalType
 * @brief Represents the types of signals that can be received via I2C.
 */
enum SignalType {
  NONE = -1,                ///< No signal or cleared state
  PASSWORD_RESET = 0,       ///< Signal to reset password
  MOTOR_LOCK_CLOSE = 1,     ///< Signal to close the motor lock
  SKIP = 2                  ///< Signal to skip authentication
};

/**
 * @brief Initializes the I2C signal handler.
 *
 * Sets up the device as an I2C slave and registers the receive callback.
 */
void setupSignalHandler();

/**
 * @brief Checks if a password reset signal has been received.
 * @return true if the signal was received, false otherwise
 */
bool isPasswordResetRequested();

/**
 * @brief Checks if a motor lock close signal has been received.
 * @return true if the signal was received, false otherwise
 */
bool isMotorLockCloseRequested();

/**
 * @brief Checks if a skip authentication signal has been received.
 * @return true if the signal was received, false otherwise
 */
bool skipAuthentication();

/**
 * @brief Clears the current signal flag.
 *
 * Resets the internal signal state to NONE.
 */
void clearSignalFlag();

#endif  // I2C_SIGNAL_HANDLER_H