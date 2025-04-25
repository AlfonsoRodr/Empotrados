/**
 * @file FingerprintImpl.cpp
 * @brief Implementation of fingerprint sensor operations using Adafruit Fingerprint library.
 *
 * This file contains the logic to initialize the fingerprint sensor, 
 * read and verify fingerprints, and provide feedback to the user through LCD display. 
 * It includes user interaction messages for successful and failed authentication attempts.
 * 
 * @see PasswordManager
 *
 * @author Alfonso Rodríguez
 * @date 2025-03-26
 */

#include "FingerprintEsp.h"
#include "PasswordManager.h"
#include <Arduino.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int opportunities = 5;

/**
 * @brief Initializes the fingerprint sensor and configures necessary hardware.
 *
 * This function sets up serial communication, configures the output pins
 * for the red and green LEDs, initializes the fingerprint sensor module and initialize the I2C communication handler.
 * It verifies whether the sensor is properly connected and operational.
 *
 * @details
 * - Begins serial communication at 9600 baud.
 * - Initializes the fingerprint sensor at 57600 baud.
 * - If the fingerprint sensor is detected and verified, it proceeds.
 * - If not detected, it prints an error message and halts execution.
 *
 * @note This function blocks indefinitely if the fingerprint sensor is not found.
 * @warning Ensure the fingerprint sensor is properly connected before powering the device.
 *
 * @see I2CCommunication Module.
 */
void setupFingerprint() {
    Serial.begin(9600);
    setupSignalHandler();
    while (!Serial);  
    delay(100);

    Serial.println("Inicializando sensor de huellas...");

    finger.begin(57600);
    delay(5);
    
    if (finger.verifyPassword()) {
        Serial.println("Fingerprint sensor online.");
    } 
    else {
        Serial.println("Error: Fingerprint sensor offline");
        while (1) { 
            delay(1000); 
        }
    }
}

/**
 * @brief Resets the number of remaining fingerprint attempts to the maximum allowed.
 * 
 * This function sets the internal `opportunities` counter back to 5,
 * which is the maximum number of fingerprint verification attempts allowed.
 * It is typically called after a successful authentication or when the system resets,
 * ensuring the user starts fresh with a full set of tries.
 */
void resetFingerOpportunities() {
    opportunities = 5;
}

/**
 * @brief Displays a success message when a fingerprint is correctly recognized.
 *
 * This function clears the LCD and shows a message indicating that a fingerprint
 * has been successfully detected. After a short delay, it welcomes the user
 * and displays their fingerprint ID.
 *
 * @note Uses `finger.fingerID` to print the ID of the recognized user.
 * @warning This function includes delays (`delay(2000)`), which may block execution for 2 seconds.
 */
void printCorrectMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fingerprint");
    lcd.setCursor(0, 1);
    lcd.print("Detected!!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome Back");
    lcd.setCursor(0, 1);
    lcd.print("User: ");
    lcd.print(finger.fingerID);
}

/**
 * @brief Reduces the remaining attempts and provides feedback.
 *
 * Decreases `opportunities` by one, displays an error message, and activates
 * a buzzer tone to signal an incorrect fingerprint attempt.
 */
void substracFingerprintTry() {
    opportunities--;
    lcd.setCursor(0, 0);
    lcd.print("Not Detected");
    lcd.setCursor(0, 1);
    lcd.print("Tries left: ");
    lcd.print(opportunities);
    delay(1000);
    tone(BUZZER, 500);
    delay(500);
    noTone(BUZZER);
    lcd.clear();
}

/**
 * @brief Executes error feedback upon incorrect fingerprint reading.
 *
 * Decrements the number of allowed attempts and provides feedback through
 * the LCD and a buzzer tone. If no attempts remain, triggers a blocking alert loop.
 *
 * @note It will unlock the system manually if the correct IR signal is received.
 */
void wrongFingerPrint() {
    if (opportunities > 0) {
        substracFingerprintTry();
    }
    if (opportunities == 0) {
        lcd.setCursor(0, 0);
        lcd.print("No tries left");
        unsigned long timeout = millis() + 10000; // The system is lock for 10 segs.
        while (millis() < timeout) {
            tone(BUZZER, 1000);
            delay(300);
            tone(BUZZER, 1500);
            delay(300);
            if (isPasswordResetRequested()) {
                clearSignalFlag();  // Reset the Signal.
                break;
            }
        }
        resetFingerOpportunities();
        resetSystem();
    }
}

/**
 * @brief Handles fingerprint recognition using the fingerprint sensor module.
 *
 * This function reads and processes a fingerprint image, then searches for a match
 * in the stored database. If a fingerprint is successfully recognized, it displays
 * a welcome message on the LCD, turns on a green LED, and prints the user ID and
 * confidence level to the serial monitor. If the fingerprint is not recognized,
 * it shows an error message and turns on a red LED briefly.
 *
 * @details
 * - If the image cannot be read or processed, an appropriate error message is printed.
 * - If the fingerprint is matched, it calls printCorrectMessage().
 * - If not matched, it calls printWrongMessage().
 */
int fingerprintSensor() {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK) {
        Serial.println("No se pudo leer la huella. Intenta de nuevo.");
        return -1;
    } 
    else {
        p = finger.image2Tz();
        if (p != FINGERPRINT_OK) {
            Serial.println("No se pudo procesar la huella.");
            delay(1000);
            return;
        }

        p = finger.fingerSearch();
        if (p == FINGERPRINT_OK) {
            resetFingerOpportunities();
            printCorrectMessage();
            Serial.print("Huella reconocida. ID: "); 
            Serial.println(finger.fingerID);
            Serial.print("Nivel de confianza: "); 
            Serial.println(finger.confidence);
            delay(5000);
            lcd.clear();
            return 1;
        } 
        else {
            Serial.println("Huella no reconocida.");
            delay(5000);
            wrongFingerPrint();
            return 0;
        }
    }
    delay(1000);
}