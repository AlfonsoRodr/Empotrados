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

#include "I2CSignalHandler.h"
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// --- Hardware Pin Definitions ---
#define BUZZER 12  ///< Digital pin connected to the buzzer

// --- External Variable Declarations ---
extern LiquidCrystal_I2C lcd;       ///< Global LCD display instance
extern int triesLeft;               ///< Number of remaining password attempts
extern bool wrongIntroducedPsw;    ///< Flag indicating whether a wrong password was introduced 

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
 * @brief Resets the number of allowed password attempts.
 *
 * Restores the attempt counter to its initial value (3), allowing for new attempts.
 */
void resetTries();

/**
 * @brief Clears the password input buffer and resets internal state.
 *
 * This function resets the current password entry, input counter, and buzzer state.
 */
void resetPasswordState();

/**
 * @brief Clears and reinitializes the LCD display.
 *
 * Displays the default password prompt message.
 */
void resetLCDScreen();

/**
 * @brief Performs a complete reset of the password system.
 *
 * Combines all individual reset routines (tries, password buffer, LCD).
 */
void resetSystem();

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
 * @brief Displays the current password input as masked characters.
 *
 * This function updates the second row of the LCD screen to show asterisks ('*')
 * corresponding to the number of characters typed by the user so far, preserving
 * confidentiality during input.
 *
 * @note Typically called from within `handlePasswordInput()` whenever a key is pressed.
 */
void printPassword();

/**
 * @brief Finalizes and validates the password entered by the user.
 *
 * Terminates the input string, sends it to the serial monitor, and clears the LCD.
 * It then checks whether the input matches the predefined password.
 * 
 * - On success: calls `correctPassword()` and resets the attempt counter.
 * - On failure: calls `wrongPassword()` and decreases the remaining attempts.
 * 
 * @return `1` if the password is correct,
 *         `0` if the password is incorrect.
 *
 * @note Triggered by pressing the 'S' key on the keypad.
 */
int submitPassword();

/**
 * @brief Deletes the last character entered into the password buffer.
 *
 * This function removes the most recent character, updates the internal counter,
 * and erases the corresponding asterisk from the LCD. The cursor is also repositioned.
 *
 * @note Triggered by pressing the 'D' key on the keypad.
 */
void deleteChar();

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
 * @brief Decreases the number of available attempts and gives user feedback.
 *
 * Updates the LCD to reflect a failed attempt and plays an alert tone.
 */
void substractTry();    

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