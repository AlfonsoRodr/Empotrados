/**
 * @file MotorLock.h
 * @author Raúl Sánchez.
 * @brief Header file for controlling a servo motor used as a lock mechanism.
 *
 * This module provides basic functions to initialize, open, and close a servo motor
 * that acts as a locking mechanism. It uses the Arduino Servo library to manage
 * servo operations.
 */

#ifndef MOTOR_LOCK_H
#define MOTOR_LOCK_H

#include <Servo.h>

#define SERVO_OPEN -90
#define SERVO_CLOSE 120
#define SERVO_PIN 13

/**
 * @brief Initializes the servo motor.
 *
 * Attaches the servo motor to the defined pin and prepares it for use.
 */
void setupServo();

/**
 * @brief Closes the servo motor (locks the mechanism).
 *
 * Moves the servo to the defined lock position (SERVO_CLOSE).
 */
void closeServo();


/**
 * @brief Opens the servo motor (unlocks the mechanism).
 *
 * Moves the servo to the defined open position (SERVO_OPEN).
 */
void openServo();

#endif