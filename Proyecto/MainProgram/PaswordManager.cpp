/**
 * @file PasswordManager.cpp
 * @brief Implementation of the password management system for Arduino using keypad input.
 *
 * This file implements the core logic of a password-based access control system,
 * including keypad handling, password verification, visual and audio feedback, and
 * a limit on incorrect attempts. It uses a 4x4 keypad, an LCD for user interaction,
 * and both a buzzer and LED for signaling feedback.
 * 
 * @authors
 * - Alfonso Rodríguez
 * - Raúl Sánchez
 * - Héctor González
 * 
 * @date 2025-04-03
 */

#include "PasswordManager.h"

// --- Keypad Configuration ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = { 
  {'H', 'O', 'L', 'A'},
  {'P', 'U', 'T', 'E'},
  {'O', '1', '9', 'C'},
  {'*', '0', 'D', 'S'}  // 'S' is used to submit the password
};

byte rowsPins[ROWS] = {11, 10, 9, 8};
byte colsPins[COLS] = {7, 6, 5, 4};

// --- Global Objects and Variables ---
Keypad teclado = Keypad(makeKeymap(keys), rowsPins, colsPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x3f, 16, 2);
int triesLeft = 3;
bool wrongIntroducedPsw = true;

const char password[7] = "HOLAPU";  ///< Predefined 6-character password
int counter = 0;                   ///< Tracks number of typed characters
char result[32];                   ///< Buffer to store entered password

/**
 * @brief Initializes the password system hardware and state.
 *
 * Sets up the LCD display, buzzer, LED, and serial communication.
 * Also initializes the password buffer for user input.
 */
void setupPasswordManager() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    pinMode(BUZZER, OUTPUT);
    pinMode(LED, OUTPUT);
    Serial.println("Sistema de contraseña listo.");
    memset(result, 0, sizeof(result));
}

/**
 * @author Alfonso Rodríguez.
 * @brief Verifies if the entered password matches the stored one.
 *
 * Compares the user-provided password with the predefined value.
 * Only passwords of exactly 6 characters are considered valid for comparison.
 *
 * @param result Character array containing the user input.
 * @return `true` if the password is correct, `false` otherwise.
 */
bool verifyPassword(char result[32]) {
    if (strlen(result) != 6) {
        return false;
    }
    return strcmp(result, password) == 0;
}

/**
 * @author Alfonso Rodríguez.
 * @brief Displays a masked password (with asterisks) on the LCD.
 *
 * Each character typed by the user is represented by an asterisk (`*`)
 * on the second line of the LCD screen to preserve confidentiality.
 */
void printPassword() {
    lcd.setCursor(0, 1);
    for (int i = 0; i <= counter; i++) {
        lcd.print('*');
    }
}

/**
 * @author Alfonso Rodríguez.
 * @brief Handles keypad input and password submission.
 *
 * This function captures user input from the keypad, updates the password buffer,
 * and displays masked characters. Upon pressing the 'S' key, the entered password 
 * is verified and appropriate actions are taken for success or failure.
 *
 * @return An integer indicating the result:
 * - `1` → Correct password
 * - `0` → Incorrect password
 * - `-1` → No submission yet (still typing)
 */
int handlePasswordInput() {
    char key = teclado.getKey();

    if ((key != 'S') && (key != NO_KEY)) {
        if (counter < 31) {
            printPassword();
            Serial.print("Tecla presionada: ");
            Serial.println(key);
            result[counter] = key;
            counter++;
        } 
        else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Password too long");
            delay(2000);
            return 0;
        }
    } 
    else if (key == 'S') {
        result[counter] = '\0';
        counter = 0;
        Serial.println(result);
        lcd.clear();
        if (verifyPassword(result)) {
            correctPassword();
            return 1;
        } 
        else {
            wrongPassword();
            return 0;
        }
    }
    return -1;
}

/**
 * @author Raúl Sánchez.
 * @brief Executes success feedback upon correct password entry.
 *
 * This function shows a confirmation message, lights up the LED, and
 * emits a short buzzer tone to indicate success.
 */
void correctPassword() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Correct password!!");
    digitalWrite(LED, HIGH);
    tone(BUZZER, 100);
    delay(300);
    noTone(BUZZER);
    delay(1000);
    lcd.clear();
}

/**
 * @author Héctor Gónzalez.
 * @brief Executes error feedback upon incorrect password entry.
 *
 * Decrements the number of allowed attempts and provides feedback through
 * the LCD and a buzzer tone. If no attempts remain, triggers a blocking alert loop.
 */
void wrongPassword() {
    if (triesLeft > 0) {
        triesLeft--;
        lcd.setCursor(0, 0);
        lcd.print("Wrong password");
        lcd.setCursor(0, 1);
        lcd.print("Tries left: ");
        lcd.print(triesLeft);
        delay(1000);
        tone(BUZZER, 500);
        delay(500);
        noTone(BUZZER);
        lcd.clear();
    }

    if (triesLeft == 0) {
        lcd.setCursor(0, 0);
        lcd.print("No tries left");
        while (true) {
            tone(BUZZER, 1000);
            delay(300);
            tone(BUZZER, 1500);
            delay(300);
        }
    }
}