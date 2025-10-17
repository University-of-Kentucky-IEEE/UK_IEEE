//
// Created by Nathan Jones on 10/9/25.
//

#include <Arduino.h>
#include "pins.h"
#include "movement.h"

void moveForward() {
    Serial.println("Forward");
    digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}

void moveBackward() {
    Serial.println("Backward");
    digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
}

void turnLeft() {
    Serial.println("Left");
    digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
}

void turnRight() {
    Serial.println("Right");
    digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}

void stopMovement() {
    Serial.println("Stop");
    digitalWrite(enableA, LOW);
    digitalWrite(enableB, LOW);
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
}