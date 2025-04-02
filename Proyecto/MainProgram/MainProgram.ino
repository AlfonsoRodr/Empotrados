/**
* @file MainProgram.ino
* @brief TBD
* @author Alfonso Rodríguez Gutt, Raúl Sánchez Benítez, Andrés Muñoz Muñoz, Héctor Gónzalez Viñas.
* @date 28/03/2025.
*/

#include "FingerprintEsp.h"
#include "PasswordEsp.h"
int nTries=3;

void setup() {
  setupFingerprint();
  setupPassword();
}

/**
* @note Luego hay que ir juntando todo de forma adecuada, pero de momento simplemente las estoy poniendo para tenerlas. 
* Pero hay que ponerlo en el orden correcto y de la forma correcta.
*/
void loop() {
  if (handlePasswordInput()) {
    fingerprintSensor();
    
  }else{
    if(nTires>0){
      //funcion1
    }else{
      //funcion2
      nTries--;
    }
  }
}