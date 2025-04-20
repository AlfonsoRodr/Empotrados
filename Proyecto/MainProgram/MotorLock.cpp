#include "motorLock.h"

Servo servo;

void setupServo(){
  servo.attach(13); // LO PUSE AHÍ PORQUE EN EL 3 ESTÁ LA HUELLA, PERO LUEGO SE PONE EL NÚMERO DE PIN CORRESPONDIENTE.
  servo.write(SERVO_CLOSE);
}

void closeServo(){
  servo.write(SERVO_CLOSE);
}

void openServo(){
  servo.write(SERVO_OPEN);
}