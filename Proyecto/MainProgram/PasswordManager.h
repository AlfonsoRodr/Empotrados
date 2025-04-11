/**
 * @file PasswordManager.h
 * @brief Interface for handling password-based access control using a keypad and LCD.
 *
 * This header file declares the core components of a password access control system
 * for Arduino. The system uses a keypad for password entry, an LCD screen for visual
 * feedback, and a buzzer and LED for status signaling. It provides user feedback for 
 * both correct and incorrect entries and enforces a limit on failed attempts.
 *
 * Intended to be used in conjunction with `PasswordManager.cpp`, this module is also 
 * compatible with additional security modules such as fingerprint readers.
 * 
 * @authors
 * - Alfonso Rodríguez  
 * - Raúl Sánchez  
 * - Héctor González
 * - Andrés Muñoz
 *
 * @date 2025-04-03
 */

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// --- Hardware Pin Definitions ---
#define BUZZER 12  ///< Digital pin connected to the buzzer
#define LED    11  ///< Digital pin connected to the status LED

// --- External Variable Declarations ---
extern LiquidCrystal_I2C lcd;       ///< Global LCD display instance
extern int triesLeft;               ///< Number of remaining password attempts
extern bool wrongIntroducedPsw;     ///< Flag indicating whether a wrong password was introduced

/**
 * @brief Initializes the password system and associated hardware.
 *
 * Sets up the LCD screen, keypad input, I/O pins (buzzer and LED), and serial communication.
 * This function should be called in the `setup()` function of the main sketch.
 *
 * @note This function assumes that the LCD and keypad hardware are connected and initialized properly.
 */
void setupPasswordManager();

/**
 * @brief Validates the entered password against a predefined value.
 *
 * Compares the entered password (passed as a character array) to a stored reference value.
 * Also verifies that the password meets expected formatting or length requirements.
 *
 * @param result A null-terminated character array containing the user's input.
 * @return `true` if the password is correct, `false` otherwise.
 */
bool verifyPassword(char result[32]);

/**
 * @brief Handles real-time keypad input and submission.
 *
 * Monitors user input via the keypad, displays the typed characters on the LCD,
 * and triggers verification once the submit key ('S') is pressed.
 *
 * @return An integer status code:
 * - `1`  → Password correct
 * - `0`  → Password incorrect
 * - `-1` → Awaiting user submission
 *
 * @note This function is non-blocking and should be called repeatedly in the main loop.
 */
int handlePasswordInput();

/**
 * @brief Executes feedback for correct password entry.
 *
 * Displays a success message on the LCD, activates the LED, and plays a tone
 * on the buzzer to confirm successful access.
 *
 * @note Typically called by `handlePasswordInput()` or similar password verification logic.
 */
void correctPassword();

/**
 * @brief Executes feedback for incorrect password entry.
 *
 * Decreases the number of remaining attempts, displays an error message, and 
 * activates the buzzer for a brief tone to alert the user.
 *
 * @note Called automatically when password verification fails.
 */
void wrongPassword();

#endif // PASSWORD_MANAGER_H