//
// Created by Nathan Jones on 10/9/25.
//

#include <Arduino.h>
#include "pins.h"
#include "movement.h"

void Movement::activateMotors() {
    Serial.println("Activate Motors");
    digitalWrite(enableAB, HIGH);
    digitalWrite(enableBB, HIGH);
    digitalWrite(enableAF, HIGH);
    digitalWrite(enableBF, HIGH);

}

void Movement::deactivateMotors() {
    Serial.println("Deactivate Motors");
    digitalWrite(enableAB, LOW);
    digitalWrite(enableBB, LOW);
    digitalWrite(enableAF, LOW);
    digitalWrite(enableBF, LOW);
}

void Movement::moveForward() {
    Serial.println("Forward");
    activateMotors();

    // Front wheels
    digitalWrite(input1F, HIGH);
    digitalWrite(input2F, LOW);
    digitalWrite(input3F, HIGH);
    digitalWrite(input4F, LOW);

    // Back wheels
    digitalWrite(input1B, HIGH);
    digitalWrite(input2B, LOW);
    digitalWrite(input3B, HIGH);
    digitalWrite(input4B, LOW);
}

void Movement::moveBackward() {
    Serial.println("Backward");
    activateMotors();

    // Front wheels
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, HIGH);
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, HIGH);

    // Back wheels
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, HIGH);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, HIGH);
}

void Movement::turnLeft() {
    Serial.println("Left");
    activateMotors();

    // A side
    digitalWrite(input1F, HIGH);
    digitalWrite(input2F, LOW);
    digitalWrite(input1B, HIGH);
    digitalWrite(input2B, LOW);

    // B side
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, HIGH);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, HIGH);
}

void Movement::turnRight() {
    Serial.println("Right");
    activateMotors();

    // A side
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, HIGH);
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, HIGH);

    // B side
    digitalWrite(input3F, HIGH);
    digitalWrite(input4F, LOW);
    digitalWrite(input3B, HIGH);
    digitalWrite(input4B, LOW);
}

void Movement::strafeLeft() {
    Serial.println("Strafe Left");
    activateMotors();

    // A side
    digitalWrite(input1F, HIGH);
    digitalWrite(input2F, LOW);
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, HIGH);

    // B side
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, HIGH);
    digitalWrite(input3B, HIGH);
    digitalWrite(input4B, LOW);
}

void Movement::strafeRight() {
    Serial.println("Strafe Right");
    activateMotors();

    // A side
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, HIGH);
    digitalWrite(input1B, HIGH);
    digitalWrite(input2B, LOW);

    // B side
    digitalWrite(input3F, HIGH);
    digitalWrite(input4F, LOW);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, HIGH);
}

void Movement::stopMovement() {
    Serial.println("Stop");
    deactivateMotors();

    // Front wheels
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, LOW);
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, LOW);

    // Back wheels
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, LOW);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, LOW);
}