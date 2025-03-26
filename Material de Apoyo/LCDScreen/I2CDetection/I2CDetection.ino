#include <Wire.h>
/* This code will detect the direction of the I2C interface. */
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Buscando dispositivos I2C...");

  Wire.begin();
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo encontrado en: 0x");
      Serial.println(i, HEX);
      delay(10);
    }
  }
}

void loop() {}