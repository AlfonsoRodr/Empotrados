#include "PasswordManager.h"
#include "FingerprintEsp.h"
#include "TemperatureFanController.h"
#include <LiquidCrystal_I2C.h>


void setup() {
  setupPasswordManager();
  setupFingerprint();
  setupTemperatureFan();
}

void loop() {
  updateTemperatureFan();
  lcd.setCursor(0, 0);
  lcd.print("Password:");
  if (handlePasswordInput() == 1) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Put your Finger");
    delay(2000);
    lcd.clear();
    fingerprintSensor();
  }
}