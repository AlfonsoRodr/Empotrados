#include "motorLock.h"

Servo servo;

void setUpServo(){
  servo.attach(3);
  servo.write(SERVO_CLOSE);
}

void closeServo(){
  servo.write(SERVO_CLOSE);
}

void openServo(){
  servo.write(SERVO_OPEN);
}
