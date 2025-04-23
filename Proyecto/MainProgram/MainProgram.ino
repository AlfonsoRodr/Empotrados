#include "PasswordManager.h"
#include "FingerprintEsp.h"
#include <LiquidCrystal_I2C.h>
#include "MotorLock.h"

bool correctFinger = false;

void setup() {
  setupPasswordManager();
  setupFingerprint();
  setupServo();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Password:");
  if (handlePasswordInput() == 1) {
    if (skipAuthentication()) {
      lcd.setCursor(0,0);
      lcd.print("Authentication");
      lcd.setCursor(0, 1);
      lcd.print("Skipped");
      delay(2000);
      clearSignalFlag();
      correctFinger = true;
    }
    else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Put your Finger");
      delay(2000);
      lcd.clear();
      for (int i = 0; i < 5; i++) {
        if (fingerprintSensor() == 1) {
          correctFinger = true;
          break;
        }
        else {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Put your Finger");
        }
      }
    }
    lcd.clear();
    if (correctFinger) {
      openServo();
    }
  }
  if (isMotorLockCloseRequested()) {
    clearSignalFlag();
    closeServo();
  }
}