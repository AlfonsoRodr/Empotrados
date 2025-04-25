/**
 * @file MotorArm.cpp
 * @author Raúl Sánchez.
 * @brief Implementation file for servo motor arm control functions.
 *
 * This file provides the implementation of functions declared in MotorArm.h,
 * allowing control of a servo motor that operates as a mechanic arm.
 */
#include "MotorArm.h"
#include <Arduino.h>

Servo arm;

/**
 * @brief Initializes the servo motor.
 *
 * Attaches the servo to the specified pin and sets it to the down position and initialize the I2C communication handler.
 */
void setupArm(){
  arm.attach(15);
  arm.write(ARM_DOWN);
}

/**
 * @brief Moves the servo mechanism to the down position.
 */
void armDown(){
    for (int pos = ARM_UP; pos <= ARM_DOWN; pos++) {
        arm.write(pos);
        delay(10);
    }
}

/**
 * @brief Moves the servo mechanism to the up position.
 */
void armUp(){
    for (int pos = ARM_DOWN; pos >= ARM_UP; pos--) {
        arm.write(pos);
        delay(10);
    }
}