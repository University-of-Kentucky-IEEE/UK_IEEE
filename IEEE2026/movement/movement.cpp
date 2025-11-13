//
// Created by Nathan Jones on 10/9/25.
//

#include <Arduino.h>
#include "pins.h"
#include "movement.h"

void Movement::rotateFront(Direction direction) {
    digitalWrite(enableAF, HIGH);
    digitalWrite(enableBF, HIGH);

    switch (direction) {
        case FORWARD:
            digitalWrite(input1F, HIGH);
            digitalWrite(input2F, LOW);
            digitalWrite(input3F, HIGH);
            digitalWrite(input4F, LOW);
            break;
        case BACKWARD:
            digitalWrite(input1F, LOW);
            digitalWrite(input2F, HIGH);
            digitalWrite(input3F, LOW);
            digitalWrite(input4F, HIGH);
            break;
        case STOP:
            digitalWrite(enableAF, LOW);
            digitalWrite(enableBF, LOW);
            digitalWrite(input1F, LOW);
            digitalWrite(input2F, LOW);
            digitalWrite(input3F, LOW);
            digitalWrite(input4F, LOW);
            break;
    }
}

void Movement::rotateBack(Direction direction) {
    digitalWrite(enableAB, HIGH);
    digitalWrite(enableBB, HIGH);

    switch (direction) {
        case FORWARD:
            digitalWrite(input1B, HIGH);
            digitalWrite(input2B, LOW);
            digitalWrite(input3B, HIGH);
            digitalWrite(input4B, LOW);
            break;
        case BACKWARD:
            digitalWrite(input1B, LOW);
            digitalWrite(input2B, HIGH);
            digitalWrite(input3B, LOW);
            digitalWrite(input4B, HIGH);
            break;
        case STOP:
            digitalWrite(enableAB, LOW);
            digitalWrite(enableBB, LOW);
            digitalWrite(input1B, LOW);
            digitalWrite(input2B, LOW);
            digitalWrite(input3B, LOW);
            digitalWrite(input4B, LOW);
    }
}

void Movement::rotateA(Direction direction) {
    digitalWrite(enableAF, HIGH);
    digitalWrite(enableAB, HIGH);

    if (direction == FORWARD) {
        digitalWrite(input1F, HIGH);
        digitalWrite(input1B, HIGH);
        digitalWrite(input2F, LOW);
        digitalWrite(input2B, LOW);
    } else {
        digitalWrite(input1F, LOW);
        digitalWrite(input1B, LOW);
        digitalWrite(input2F, HIGH);
        digitalWrite(input2B, HIGH);
    }
}

void Movement::rotateB(Direction direction) {
    digitalWrite(enableBF, HIGH);
    digitalWrite(enableBB, HIGH);

    if (direction == FORWARD) {
        digitalWrite(input3F, HIGH);
        digitalWrite(input3B, HIGH);
        digitalWrite(input4F, LOW);
        digitalWrite(input4B, LOW);
    } else {
        digitalWrite(input3F, LOW);
        digitalWrite(input3B, LOW);
        digitalWrite(input4F, HIGH);
        digitalWrite(input4B, HIGH);
    }
}

void Movement::moveForward() {
    Movement::state = State::MOVE_FORWARD;

    Serial.println("Forward");
    rotateFront(FORWARD);
    rotateBack(FORWARD);
}

void Movement::moveBackward() {
    Movement::state = State::MOVE_BACKWARD;

    Serial.println("Backward");
    rotateFront(BACKWARD);
    rotateBack(BACKWARD);
}

void Movement::turnLeft() {
    Movement::state = State::TURN_LEFT;

    Serial.println("Turn Left");
    /*digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);*/
    rotateA(FORWARD);
    rotateB(BACKWARD);
}

void Movement::turnRight() {
    Movement::state = State::TURN_RIGHT;

    Serial.println("Turn Right");
    /*digitalWrite(enableA, HIGH);
    digitalWrite(enableB, HIGH);

    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);*/
    rotateA(BACKWARD);
    rotateB(FORWARD);
}

void Movement::stopMovement() {
    Movement::state = State::STOPPED;

    Serial.println("Stop");
    /*
    digitalWrite(enableAF, LOW);
    digitalWrite(enableAB, LOW);
    digitalWrite(enableBF, LOW);
    digitalWrite(enableBB, LOW);

    // A/Left side
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, LOW);
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, LOW);

    // B/Right side
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, LOW);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, LOW);
    */
    rotateFront(STOP);
    rotateBack(STOP);
}

void Movement::strafeRight() {
    Movement::state = State::MOVE_RIGHT;

    Serial.println("Right");
    /*digitalWrite(enableAF, HIGH);
    digitalWrite(enableAB, HIGH);
    digitalWrite(enableBF, HIGH);
    digitalWrite(enableBB, HIGH);
    digitalWrite(input1F, HIGH);
    digitalWrite(input2F, LOW);
    digitalWrite(input3F, HIGH);
    digitalWrite(input4F, LOW);
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, HIGH);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, HIGH);*/
    rotateFront(FORWARD);
    rotateBack(BACKWARD);
}

void Movement::strafeLeft() {
    Movement::state = State::MOVE_LEFT;

    Serial.println("Left");
    /*digitalWrite(enableAF, HIGH);
    digitalWrite(enableAB, HIGH);
    digitalWrite(enableBF, HIGH);
    digitalWrite(enableBB, HIGH);
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, HIGH);
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, HIGH);
    digitalWrite(input1B, HIGH);
    digitalWrite(input2B, LOW);
    digitalWrite(input3B, HIGH);
    digitalWrite(input4B, LOW);*/
    rotateFront(BACKWARD);
    rotateBack(FORWARD);
}

Movement::State Movement::state = Movement::State::STOPPED;

