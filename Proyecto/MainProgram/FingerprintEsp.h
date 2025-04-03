/**
* @file FingerprintEsp.h
* @brief Especification of the operations for the Fingerprint sensor.
* @author Alfonso Rodríguez.
* @date 26/03/2025.
*/

#ifndef FINGERPRINTMODULE_H
#define FINGERPRINTMODULE_H

#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;
#else
#define mySerial Serial1
#endif

extern Adafruit_Fingerprint finger;
extern int ledRojo;
extern int ledVerde;

void setupFingerprint();
void fingerprintSensor();

#endif