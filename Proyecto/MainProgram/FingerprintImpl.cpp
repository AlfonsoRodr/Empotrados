/**
* @file FingerprintImpl.cpp
* @brief Implementation of the operations for the Fingerprint sensor.
* @author Alfonso Rodríguez.
* @date 26/03/2025.
*/

#include "FingerprintEsp.h"
#include <Arduino.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int ledRojo = A0;
int ledVerde = A1;

void setupFingerprint() {
    Serial.begin(9600);
    while (!Serial);  
    delay(100);

    pinMode(ledRojo, OUTPUT);
    pinMode(ledVerde, OUTPUT);

    Serial.println("Inicializando sensor de huellas...");

    finger.begin(57600);
    delay(5);
    
    if (finger.verifyPassword()) {
        Serial.println("Fingerprint sensor online.");
    } 
    else {
        Serial.println("Error: Fingerprint sensor offline");
        while (1) { 
            delay(1000); 
        }
    }
}

void fingerprintSensor() {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK) {
        digitalWrite(ledRojo, LOW);
        Serial.println("No se pudo leer la huella. Intenta de nuevo.");
    } else {
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