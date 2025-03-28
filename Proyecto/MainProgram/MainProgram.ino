/**
* @file MainProgram.ino
* @brief TBD
* @author Alfonso Rodríguez Gutt, Raúl Sánchez Benítez, Andrés Muñoz Muñoz, Héctor Gónzalez Viñas.
* @date 28/03/2025.
*/

#include "FingerprintEsp.h"
#include "PasswordEsp.h"

void setup() {
  setupFingerprint();
}

void loop() {
  fingerprintSensor();
}