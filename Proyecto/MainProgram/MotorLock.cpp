/**
 * @file MotorLock.cpp
 * @author Raúl Sánchez.
 * @brief Implementation file for servo motor lock control functions.
 *
 * This file provides the implementation of functions declared in MotorLock.h,
 * allowing control of a servo motor that operates as a locking mechanism.
 */
#include "MotorLock.h"

Servo servo;

/**
 * @brief Initializes the servo motor.
 *
 * Attaches the servo to the specified pin and sets it to the locked position and initialize the I2C communication handler.
 *
 * @see I2CCommunication module.
 */
void setupServo(){
  setupSignalHandler();
  servo.attach(14);
  servo.write(SERVO_CLOSE);
}

/**
 * @brief Locks the mechanism by moving the servo to the closed position.
 */
void closeServo(){
  servo.write(SERVO_CLOSE);
}

/**
 * @brief Unlocks the mechanism by moving the servo to the open position.
 */
void openServo(){
  servo.write(SERVO_OPEN);
}