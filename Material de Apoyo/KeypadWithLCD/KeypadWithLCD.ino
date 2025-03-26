/**
* @file KeyPadWithLCD.ino
* @brief This file will print in a LCD screen, the value for the key pressed at the keypad.
* @author Alfonso Rodríguez.
* @date 01/03/2025.
*/

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dimensions of the keypad
const byte FILAS = 4;
const byte COLUMNAS = 4;

// Setting the keys
char teclas[FILAS][COLUMNAS] = { 
  {'R', 'A', 'U', 'L'},
  {'P', 'U', 'T', 'E'},
  {'O', '1', '9', 'C'},
  {'*', '0', '#', ' '}
};

// Conections
byte pinesFilas[FILAS] = {9, 8, 7, 6};    
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2}; 

// Keypad initializer.
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// LCD I2C direction.
LiquidCrystal_I2C lcd(0x3f, 16, 2);

//
int contador = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Presione tecla:");
  while (!teclado.getKey()); // The welcome message will appear until a key is pressed.
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() { 
  char tecla = teclado.getKey();
  if (tecla) {
    if (contador >= 16) {  // End of the first line
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
    if (tecla == 'R') { // This key will have a delete action
      lcd.clear();
      contador = 0;
      lcd.setCursor(0, 0);
      return; // With this, the key won´t be display at the screen.
    }
  }
}