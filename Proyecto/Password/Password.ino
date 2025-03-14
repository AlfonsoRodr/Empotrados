/**
 * @file Password.ino
 * @brief Reads a password from a keypad and verifies it when the user presses "S" (Submit).
 * @author Alfonso Rodríguez.
 * @date 14/03/2025.
 */

#include <Keypad.h>
#include <Wire.h>
#include <string.h>
//#include <LiquidCrystal_I2C.h>

// Dimensions of the keypad
const byte FILAS = 4;
const byte COLUMNAS = 4;

// Setting the keys
char teclas[FILAS][COLUMNAS] = { 
  {'H', 'O', 'L', 'A'},
  {'P', 'U', 'T', 'E'},
  {'O', '1', '9', 'C'},
  {'*', '0', 'D', 'S'}
};

// Correct password (6 chars + '\0' terminator)
const char password[7] = "HOLAPU";  
char result[32] = {0};  // Initialize buffer to zero

// Connections
byte pinesFilas[FILAS] = {9, 8, 7, 6};    
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2}; 

// Keypad initializer.
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// Variables
int contador = 0;

void setup() {
  Serial.begin(9600);
  /*lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Presione tecla:");
  while (!teclado.getKey()); // The welcome message will appear until a key is pressed.
  lcd.clear();
  lcd.setCursor(0, 0); */
}

/**
* @brief It will verify is the passowrd introduced by the user matches the correct one.
* @param result is the array where the characters entered by the user are stored.
* @return true if both strings matches (the password), false otherwise.
*/
bool verifyPassword(char result[32]) {
  result[contador] = '\0';  // Ensure string termination.
  if (strlen(result) != 6) {
    return false;  // Incorrect length
  }
  return strcmp(result, password) == 0;  // Compare passwords
}

/**
* @brief This is the method that will manage the password entered by the user, and verify if it is correct.
* @param result is the array where the characters entered by the user are stored.
* @note ESTE MÉTODO ES EL QUE SE VA A USAR EN EL ARCHIVO PRINCIPAL.
*/
void password(char result[32]) {
  char tecla = teclado.getKey();
  if (tecla) {
    if (tecla != 'S') {
      if (contador < sizeof(result) - 1) {  // Prevent overflow
        Serial.print("Tecla presionada: ");
        Serial.println(tecla);
        result[contador] = tecla;
        contador++;
      } 
      else {
        Serial.println("Contraseña Incorrecta!");
      }
    } 
    else {  // If 'S' is pressed, verify password.
      result[contador] = '\0';  // Ensure null-termination.
      if (verifyPassword(result)) {
        Serial.println("Contraseña Correcta!!");
        while (true);  // Stop execution.
      } 
      else {
        Serial.println("Contraseña Incorrecta!");
      }
      // Reset input
      contador = 0;
      memset(result, 0, sizeof(result));  // Clear array.
    }
  }
}

void loop() { 
  char tecla = teclado.getKey();
  if (tecla) {
    if (tecla != 'S') {
      if (contador < sizeof(result) - 1) {  // Prevent overflow
        Serial.print("Tecla presionada: ");
        Serial.println(tecla);
        result[contador] = tecla;
        contador++;
      } 
      else {
        Serial.println("Contraseña Incorrecta!");
      }
    } 
    else {  // If 'S' is pressed, verify password.
      result[contador] = '\0';  // Ensure null-termination.
      if (verifyPassword(result)) {
        Serial.println("Contraseña Correcta!!");
        while (true);  // Stop execution.
      } 
      else {
        Serial.println("Contraseña Incorrecta!");
      }
      // Reset input
      contador = 0;
      memset(result, 0, sizeof(result));  // Clear array.
    }
  }
}
    /*if (contador >= 16) {  // End of the first line
      lcd.setCursor(contador - 16, 1);
    } 
    else {
      lcd.setCursor(contador, 0);
    }
    lcd.print(tecla);
    contador++;
    if (contador > 32) { // End of the second line
      lcd.clear();
      contador = 0;
    } 
    if (tecla == 'D') { // This key will have a delete action
      lcd.clear();
      contador = 0;
      lcd.setCursor(0, 0);
      return; // With this, the key won´t be display at the screen.
    } */
  //}
//}