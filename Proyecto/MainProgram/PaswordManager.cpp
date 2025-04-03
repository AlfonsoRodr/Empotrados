/**
 * @file PasswordManager.cpp
 * @author Alfonso Rodríguez, Rául Sánchez, Héctor Gónzalez.
 * @brief Password management system for Arduino using keypad input.
 * 
 * @date 2025-04-03
 */

#include "PasswordManager.h"

// Keypad Definition
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = { 
  {'H', 'O', 'L', 'A'},
  {'P', 'U', 'T', 'E'},
  {'O', '1', '9', 'C'},
  {'*', '0', 'D', 'S'}
};

// Keypad PINs
byte rowsPins[ROWS] = {9, 8, 7, 6};    
byte colsPins[COLS] = {5, 4, 3, 2}; 

// Keypad object creation
Keypad teclado = Keypad(makeKeymap(keys), rowsPins, colsPins, ROWS, COLS);

// LCD and hardware
LiquidCrystal_I2C lcd(0x3f, 16, 2);
int triesLeft = 3;
bool wrongIntroducedPsw = true;

// Password Variables
const char password[7] = "HOLAPU";  
int counter = 0;
char result[32];

/**
 * @brief Initializes all components and hardware (keypad, LCD, and I/O pins).
 *
 * This function is used to initialize the serial communication, LCD screen, 
 * buzzer, and LED. It also sets up the necessary configurations for the 
 * keypad and clears the password entry array.
 */
void setupPasswordManager() {
    Serial.begin(9600);
    lcd.init(); // Initialize the LCD Screen.
    lcd.backlight();
    lcd.clear();
    pinMode(BUZZER, OUTPUT);
    pinMode(LED, OUTPUT);
    Serial.println("Sistema de contraseña listo.");
    memset(result, 0, sizeof(result));  // Initialize the array.
}

/**
 * @author Alfonso Rodríguez.
 * @brief Verifies if the entered password matches the predefined password.
 *
 * This function checks if the length of the entered password is 6 characters
 * and if it matches the predefined password.
 *
 * @param result A character array that contains the entered password.
 * @return Returns true if the entered password is correct, false otherwise.
 */
bool verifyPassword(char result[32]) {
    if (strlen(result) != 6) {
        return false;
    }
    return strcmp(result, password) == 0;
}

/**
 * @author Alfonso Rodríguez.
 * @brief Handles the user input for password entry.
 *
 * This function continuously reads keys from the keypad, displays the entered
 * keys on the LCD screen, and updates the result array with the entered keys.
 * When the 'S' key is pressed, it verifies the entered password.
 */
void handlePasswordInput() {
    char key = teclado.getKey();

    if ((key != 'S') && (key != NO_KEY)) {  // If it is not the submit key (S) and the empty key, then read the input key.
        if (counter < 31) {  // Verifies if there are any space in the array.
            // Print the key in the LCD Screen
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(key);

            // Print the key in the Serial Monitor
            Serial.print("Tecla presionada: ");
            Serial.println(key);  // Muestra la tecla en el monitor serial
            result[counter] = key;
            counter++;
        }
        else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Password is too long");
            delay(2000);
            return; // Finish it due to the error.
        }
    } 
    else if (key == 'S') {  // If 'S' is pressed, verify the password.
        result[counter] = '\0';
        counter = 0;  // Reset
        Serial.println(result);
        Serial.println();
        lcd.clear();
        if (verifyPassword(result)) {
            correctPassword();
        }
        else {
            wrongPassword();
        }
    }
}

/**
 * @author Raúl Sánchez.
 * @brief Handles the actions after the correct password is entered.
 *
 * This function will display a success message on the LCD, activate the LED,
 * and generate a tone from the buzzer.
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
 * @brief Handles the actions after the incorrect password is entered.
 *
 * This function will display an error message on the LCD, decrease the number
 * of remaining tries, and activate the buzzer to alert the user of the wrong
 * password.
 */
void wrongPassword() {
    if (triesLeft > 0) {
        triesLeft--;
        lcd.setCursor(0, 0);
        lcd.print("Wrong password ");
        lcd.setCursor(0, 1);
        lcd.print("tries left: ");
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