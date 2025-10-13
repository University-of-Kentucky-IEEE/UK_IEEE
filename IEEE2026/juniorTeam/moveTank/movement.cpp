//
// Created by Nathan Jones on 10/9/25.
//
//#include "../../Libraries/ArduinoCore-avr-master/cores/arduino/Arduino.h"
//#include "../../Libraries/Stepper-master/src/Stepper.h"
#include <Stepper.h>
#include "movement.h"

extern Stepper stepper1;
extern Stepper stepper2;

void moveForward(int steps) {
    Serial.println("Forward");
    stepper1.step(steps);
    stepper2.step(-steps);
}

void moveBackward(int steps) {
    Serial.println("Backward");
    stepper1.step(-steps);
    stepper2.step(steps);
}

void turnLeft(int steps) {
    Serial.println("Left");
    stepper1.step(steps);
    stepper2.step(steps);
}

void moveRight(int steps) {
    Serial.println("Right");
    stepper1.step(-steps);
    stepper2.step(-steps);
}