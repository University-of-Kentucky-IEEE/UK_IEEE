//#include "../../Libraries/ArduinoCore-avr-master/cores/arduino/Arduino.h"
//#include "../../Libraries/Stepper-master/src/Stepper.h"
#include <Stepper.h>
#include "pins.h"
#include "movement.h"
const int stepsPerRevolution = 200;



void setup() {
    Serial.begin(115200);
    // Set pins as outputs
    pinMode(enableA, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    pinMode(input3, OUTPUT);
    pinMode(input4, OUTPUT);

    // Set all pins to low (off)
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
}

void loop() {
    digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    moveForward();
    delay(500);

    moveBackward();
    delay(500);

//    turnLeft();
//    delay(500);
//
//    turnRight();
//    delay(500);

    stopMovement();
}