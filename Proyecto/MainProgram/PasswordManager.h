/**
 * @file PasswordManager.h
 * @author Alfonso Rodríguez, Rául Sánchez, Héctor Gónzalez.
 * @brief Header file for managing password functionality in an Arduino project.
 * 
 * This file declares the necessary functions, variables, and hardware configurations 
 * for password management in an Arduino-based system using a keypad, LCD, and buzzer.
 * 
 * @date 2025-04-03
 */

#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Definition for Pins and hardware
#define BUZZER 10
#define LED 11

// External declaration of variables
extern LiquidCrystal_I2C lcd;
extern int triesLeft;
extern bool wrongIntroducedPsw;

/**
 * @brief Initializes the password management system.
 * 
 * This function sets up the necessary hardware configurations for the keypad, 
 * LCD screen, and I/O pins. It also initializes the serial communication.
 */
void setupPasswordManager();

/**
 * @brief Verifies if the entered password matches the predefined password.
 * 
 * This function compares the entered password with the predefined password to 
 * check if they match. It ensures the entered password has the correct length.
 * 
 * @param result A character array containing the entered password.
 * @return Returns true if the entered password is correct, false otherwise.
 */
bool verifyPassword(char result[32]);

/**
 * @brief Handles the user input for password entry.
 * 
 * This function reads key presses from the keypad, updates the display, and 
 * checks the entered password when the submit key is pressed. If the password 
 * is correct, it triggers the correct password actions. If incorrect, it 
 * triggers the wrong password actions.
 */
void handlePasswordInput();

/**
 * @brief Actions to take when the correct password is entered.
 * 
 * This function will display a success message, activate the LED, and generate 
 * a tone on the buzzer to indicate that the correct password has been entered.
 */
void correctPassword();

/**
 * @brief Actions to take when the wrong password is entered.
 * 
 * This function will decrement the number of remaining password attempts and 
 * display an error message. It also activates the buzzer for feedback on the wrong password.
 */
void wrongPassword();

#endif // PASSWORD_MANAGER_H