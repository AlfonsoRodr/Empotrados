/**
 * @file PasswordImpl.cpp
 * @brief Implementation of the operations related to the password management.
 * @author Alfonso Rodríguez.
 * @date 14/03/2025.
 */

#include "PasswordModule.h"
#include <Arduino.h>

// Definición del teclado
char teclas[FILAS][COLUMNAS] = { 
  {'H', 'O', 'L', 'A'},
  {'P', 'U', 'T', 'E'},
  {'O', '1', '9', 'C'},
  {'*', '0', 'D', 'S'}
};

// Contraseña correcta
const char password[7] = "HOLAPU";  

// Definición de pines
byte pinesFilas[FILAS] = {9, 8, 7, 6};    
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2}; 

// Creación del objeto Keypad
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// Variables
char result[32] = {0};
int contador = 0;

void setupPassword() {
    Serial.begin(9600);
    Serial.println("Sistema de contraseña listo.");
}

/**
* @brief It will verify is the passowrd introduced by the user matches the correct one.
* @param result is the array where the characters entered by the user are stored.
* @return true if both strings matches (the password), false otherwise.
*/
bool verifyPassword(char result[32]) {
    result[contador] = '\0';  // Asegurar terminación de cadena
    if (strlen(result) != 6) {
        return false;
    }
    return strcmp(result, password) == 0;
}

/**
* @brief This is the method that will manage the password entered by the user, and verify if it is correct.
* @note HAY QUE VER SI FUNCIONA SIN PASARLE EL ARRAY DONDE SE ALMACENA LO QUE META EL USUARIO.
*/
void handlePasswordInput() {
    char tecla = teclado.getKey();
    if (tecla) {
        if (tecla != 'S') {
            if (contador < sizeof(result) - 1) {  // Evitar desbordamiento
                Serial.print("Tecla presionada: ");
                Serial.println(tecla);
                result[contador] = tecla;
                contador++;
            } 
            else {
                Serial.println("Contraseña Incorrecta!");
            }
        } 
        else {  // Si se presiona 'S', verificar la contraseña
            result[contador] = '\0';
            if (verifyPassword(result)) {
                Serial.println("Contraseña Correcta!!");
                while (true);  // Detener ejecución
            } 
            else {
                Serial.println("Contraseña Incorrecta!");
            }
            // Reiniciar entrada
            contador = 0;
            memset(result, 0, sizeof(result));
        }
    }
}