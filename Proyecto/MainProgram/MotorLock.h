#ifndef MOTOR_LOCK_H
#define MOTOR_LOCK_H

#include <Servo.h>


#define SERVO_OPEN -90
#define SERVO_CLOSE 120


void setUpServo();

void closeServo();

void openServo();

#endif


