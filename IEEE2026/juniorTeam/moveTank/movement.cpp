//
// Created by Nathan Jones on 10/9/25.
//

#include <Arduino.h>
#include <Stepper.h>
#include "pins.h"
#include "movement.h"

extern Stepper stepper1;
extern Stepper stepper2;

void moveForward() {
    Serial.println("Forward");
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}

void moveBackward() {
    Serial.println("Backward");
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
}

void turnLeft() {
    Serial.println("Left");
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
}

void moveRight() {
    Serial.println("Right");
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}

void stopMovement() {
    Serial.println("Stop");
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
}