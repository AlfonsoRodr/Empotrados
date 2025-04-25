/**
 * @file MotorLock.h
 * @author Raúl Sánchez.
 * @brief Header file for controlling a servo motor used as a mechanic arm.
 *
 * This module provides basic functions to initialize and move servo motor that acts as a mechanic arm.
 */

#ifndef MOTOR_ARM_H
#define MOTOR_ARM_H

#include <Servo.h>

#define ARM_UP 45
#define ARM_DOWN 160

/**
 * @brief Initializes the servo motor.
 *
 * Attaches the servo motor to the defined pin and prepares it for use.
 */
void setupArm();

/**
 * @brief Moves up the servo motor.
 *
 * Moves the servo to the defined up position (ARM_UP).
 */
void armUp();


/**
 * @brief Moves down the servo motor.
 *
 * Moves the servo to the defined down position (ARM_DOWN).
 */
void armDown();

#endif