#include "PasswordManager.h"
#include "FingerprintEsp.h"
#include "TemperatureFanController.h"
#include <LiquidCrystal_I2C.h>
#inlcude "MotorLock.h"

void setup() {
  setupPasswordManager();
  setupFingerprint();
  setupTemperatureFan();
  setupServo();
}

void loop() {
  updateTemperatureFan(); // IT IS POSSIBLE THAT IT WILL BE MOVED TO OTHER ARDUINO.
  lcd.setCursor(0, 0);
  lcd.print("Password:");
  if (handlePasswordInput() == 1) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Put your Finger");
    delay(2000);
    lcd.clear();
    fingerprintSensor();
    openServo();
    
  }
}
