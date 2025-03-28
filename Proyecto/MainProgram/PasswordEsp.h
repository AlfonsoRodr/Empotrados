/**
 * @file PasswordEsp.h
 * @brief Especification of the operations related to the password management.
 * @author Alfonso Rodríguez.
 * @date 14/03/2025.
 */

#ifndef PASSWORDMODULE_H
#define PASSWORDMODULE_H

#include <Keypad.h>
#include <Wire.h>
#include <string.h>

// Definición del teclado
const byte FILAS = 4;
const byte COLUMNAS = 4;

// Mapeo del teclado
extern char teclas[FILAS][COLUMNAS];

// Pines de conexión
extern byte pinesFilas[FILAS];
extern byte pinesColumnas[COLUMNAS];

// Objeto Keypad
extern Keypad teclado;

// Buffer de entrada del usuario
extern char result[32];
extern int contador;

// Funciones
void setupPassword();
bool verifyPassword(char result[32]);
void handlePasswordInput();

#endif