#include <Keypad.h>

// Dimension of the matrix.
const byte FILAS = 4;
const byte COLUMNAS = 4;

// This is where the values for each button are established.
char teclas[FILAS][COLUMNAS] = { // This are the value for each button. The value is customizable.
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections pins.
byte pinesFilas[FILAS] = {9, 8, 7, 6};    
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2}; 

// makeKeymap(valuesForEachButton, rowPins, colsPins, numberOfRows, numberOfCols)
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char tecla = teclado.getKey(); // It will obtain the value of a specific key when its pressed.
  if (tecla) {
    Serial.print("Tecla presionada: ");
    Serial.println(tecla);
  }
}