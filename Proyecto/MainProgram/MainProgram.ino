#include "PasswordManager.h"
#include "FingerprintEsp.h"
#include <LiquidCrystal_I2C.h>

void setup() {
  setupPasswordManager();
  setupFingerprint();
}

void loop() {
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