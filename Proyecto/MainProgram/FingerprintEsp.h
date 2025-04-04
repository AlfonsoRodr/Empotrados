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
 * @brief Performs a fingerprint scan and verifies the identity.
 *
 * This function captures an image from the fingerprint sensor,
 * converts it to a template, and attempts to match it with stored fingerprints.
 * It provides visual feedback using LEDs and LCD messages.
 */
void fingerprintSensor();

#endif // FINGERPRINTMODULE_H