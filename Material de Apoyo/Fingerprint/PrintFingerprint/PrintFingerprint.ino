#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Esperar a que el puerto serie esté listo
  delay(100);
  
  Serial.println("Inicializando sensor de huellas...");

  finger.begin(57600);
  delay(5);
  
  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas detectado.");
  } else {
    Serial.println("Error: No se detectó el sensor de huellas.");
    while (1) { delay(1000); }  // No continuar si el sensor no se detecta
  }

  // Obtener el número de huellas almacenadas en el sensor
  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    Serial.println("No hay huellas almacenadas. Registra una antes de continuar.");
    while (1) { delay(1000); }
  } else {
    Serial.print("El sensor tiene "); Serial.print(finger.templateCount); Serial.println(" huellas almacenadas.");
  }
}

void loop() {
  Serial.println("Coloca tu dedo en el sensor...");
  
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) {
    Serial.println("No se pudo leer la huella. Intenta de nuevo.");
    delay(1000);
    return;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    Serial.println("No se pudo procesar la huella.");
    delay(1000);
    return;
  }

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.print("Huella reconocida. ID: "); Serial.println(finger.fingerID);
    Serial.print("Nivel de confianza: "); Serial.println(finger.confidence);
  } else {
    Serial.println("Huella no reconocida.");
  }

  delay(2000);
}
