/**
* @file FingerprintModule.ino
* @brief In this file, all the operations related to the fingerprint is managed.
* @author Alfonso Rodríguez Gutt.
*/

#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int ledRojo = 7;
int ledVerde = 6;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Esperar a que el puerto serie esté listo
  delay(100);

  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  
  Serial.println("Inicializando sensor de huellas...");

  finger.begin(57600);
  delay(5);
  
  if (finger.verifyPassword()) {
    Serial.println("Fingerorint sensor online.");
  } 
  else {
    Serial.println("Error: Fingerprint sensor offline");
    while (1) { 
      delay(1000); 
    }  // If the sensor is not detected, wait
  }
}
 
/**
* @brief This method will manage the lecture of the fingerprint. TBD.
* @note This is the method that will be used in the main program.
* @author Alfonso Rodríguez Gutt.
*/
void fingerprintSensor() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) {
    digitalWrite(ledRojo, LOW);
    Serial.println("No se pudo leer la huella. Intenta de nuevo.");
  }
  else {
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK) {
      digitalWrite(ledRojo, LOW);
      Serial.println("No se pudo procesar la huella.");
      delay(1000);
      return;
    }

    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK) {
      digitalWrite(ledRojo, LOW);
      Serial.print("Huella reconocida. ID: "); 
      Serial.println(finger.fingerID);
      Serial.print("Nivel de confianza: "); 
      Serial.println(finger.confidence);
      digitalWrite(ledVerde, HIGH);
      delay(5000);
      digitalWrite(ledVerde, LOW);
    } 
    else {
      Serial.println("Huella no reconocida.");
      digitalWrite(ledRojo, HIGH);
      delay(5000);
    }
    delay(2000);
}

void loop() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) {
    digitalWrite(ledRojo, LOW);
    Serial.println("No se pudo leer la huella. Intenta de nuevo.");
  }
  else {
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK) {
      digitalWrite(ledRojo, LOW);
      Serial.println("No se pudo procesar la huella.");
      delay(1000);
      return;
    }

    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK) {
      digitalWrite(ledRojo, LOW);
      Serial.print("Huella reconocida. ID: "); 
      Serial.println(finger.fingerID);
      Serial.print("Nivel de confianza: "); 
      Serial.println(finger.confidence);
      digitalWrite(ledVerde, HIGH);
      delay(5000);
      digitalWrite(ledVerde, LOW);
    } 
    else {
      Serial.println("Huella no reconocida.");
      digitalWrite(ledRojo, HIGH);
      delay(5000);
    }
  }
  delay(2000);
}