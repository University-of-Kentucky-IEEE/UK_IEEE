#include "../../Libraries/ArduinoCore-avr-master/cores/arduino/Arduino.h"
#include "../../Libraries/Stepper-master/src/Stepper.h"
//#include <Stepper.h>
#include "pins.h"
#include "movement.h"
const int stepsPerRevolution = 200;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper1(stepsPerRevolution, STEPPER1_P0, STEPPER1_P1, STEPPER1_P2, STEPPER1_P3);
Stepper myStepper2(stepsPerRevolution, STEPPER2_P0, STEPPER2_P1, STEPPER2_P2, STEPPER2_P3);

void setup() {
    // set the speed at 60 rpm:
    myStepper1.setSpeed(60);
    myStepper2.setSpeed(60);
    // initialize the serial port:
    Serial.begin(9600);
}

void loop() {
    moveForward(stepsPerRevolution);
    delay(500);

    moveBackward(stepsPerRevolution);
    delay(500);

    turnLeft(stepsPerRevolution);
    delay(500);

    turnRight(stepsPerRevolution);
    delay(500);
}