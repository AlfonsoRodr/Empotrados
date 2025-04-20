#include "PasswordManager.h"
#include "FingerprintEsp.h"
#include "TemperatureFanController.h"
#include <LiquidCrystal_I2C.h>
#include "MotorLock.h"

bool correctFinger = false;

void setup() {
  setupPasswordManager();
  setupFingerprint();
  //setupTemperatureFan();
  setupServo();
}

void loop() {
  //updateTemperatureFan(); // IT IS POSSIBLE THAT IT WILL BE MOVED TO OTHER ARDUINO.
  lcd.setCursor(0, 0);
  lcd.print("Password:");
  if (handlePasswordInput() == 1) {
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
    lcd.clear();
    if (correctFinger) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Piola");
      delay(2000);
      Serial.println("Piola");
      openServo();
    }
  }
}