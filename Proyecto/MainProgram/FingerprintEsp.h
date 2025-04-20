/**
 * @file FingerprintEsp.h
 * @brief Specification of operations related to the fingerprint sensor module.
 *
 * This header file declares the functions and variables necessary to interface
 * with a fingerprint sensor using the Adafruit Fingerprint library.
 * It supports both SoftwareSerial (for AVR/ESP8266 boards) and hardware serial
 * for other boards like the ATmega2560.
 * 
 * @author Alfonso Rodríguez
 * @date 2025-03-26
 */

#ifndef FINGERPRINTMODULE_H
#define FINGERPRINTMODULE_H

#include <Adafruit_Fingerprint.h>
#include "PasswordManager.h"

#define BUZZER 12  ///< Digital pin connected to the buzzer

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>

/**
 * @brief Software serial instance used for communication with the fingerprint sensor.
 */
extern SoftwareSerial mySerial;
#else
/**
 * @brief Hardware serial port used for fingerprint sensor communication on supported boards.
 */
#define mySerial Serial1
#endif

/**
 * @brief Instance of the Adafruit_Fingerprint class used to control the sensor.
 */
extern Adafruit_Fingerprint finger;

/**
 * @brief Pin number for the red LED used to indicate failure or error.
 */
extern int ledRojo;

/**
 * @brief Pin number for the green LED used to indicate success.
 */
extern int ledVerde;

/**
 * @brief Initializes the fingerprint sensor and verifies connectivity.
 *
 * This function sets up the serial interface with the fingerprint sensor,
 * configures LEDs, and checks if the sensor is connected and functional.
 */
void setupFingerprint();

/**
 * @brief Resets the fingerprint verification attempt counter to its initial value.
 * 
 * This function restores the number of allowed fingerprint attempts, enabling the user
 * to retry fingerprint verification after either a successful login, a system reset,
 * or a temporary lockout due to multiple failed attempts.
 * 
 * It is typically called when the password is verified successfully or after the system
 * has been reset through serial communication or timeout expiration.
 * 
 * @note This function works similarly to `resetTries()` from the password manager module.
 */
void resetFingerOpportunities();

/**
 * @brief Displays a success message when the fingerprint is correctly recognized.
 * 
 * This function shows in the LCD screen the ID of the user whose fingerprint has been recognized.
 */
void printCorrectMessage();

/**
 * @brief Decreases the number of available attempts and gives user feedback.
 *
 * Updates the LCD to reflect a failed attempt and plays an alert tone.
 */
void substracFingerprintTry();

/**
 * @brief Handles serial input for external system reset command.
 *
 * Listens for incoming data over serial. If TBD is received, resets the system.
 *
 * @return `true` if a reset signal was received, `false` otherwise.
 */
bool fingerprintSerialCom();

/**
 * @brief Executes feedback for incorrect fingerprint reading.
 *
 * Decreases the number of remaining attempts, displays an error message, and 
 * activates the buzzer for a brief tone to alert the user.
 *
 * @note Called automatically when fingerprint verification fails.
 */
void wrongFingerPrint();

/**
 * @brief Performs a fingerprint scan and verifies the identity.
 *
 * This function captures an image from the fingerprint sensor,
 * converts it to a template, and attempts to match it with stored fingerprints.
 * It provides visual feedback using LEDs and LCD messages.
 */
int fingerprintSensor();

#endif // FINGERPRINTMODULE_H