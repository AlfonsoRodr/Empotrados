/**
* @file MainProgram.ino
* @brief TBD
* @author Alfonso Rodríguez Gutt, Raúl Sánchez Benítez, Andrés Muñoz Muñoz, Héctor Gónzalez Viñas.
*/

#include "FingerprintEsp.h"

void setup() {
  setupFingerprint();
}

void loop() {
  fingerprintSensor();
}