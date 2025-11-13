#include <Arduino.h>
#include <Stepper.h>

#include "movement.h"
#include "pins.h"

void setup() {
    Serial.begin(9600);
    // Set pins as outputs
    pinMode(enableAF, OUTPUT);
    pinMode(enableBF, OUTPUT);
    pinMode(enableAB, OUTPUT);
    pinMode(enableBB, OUTPUT);
    pinMode(input1F, OUTPUT);
    pinMode(input2F, OUTPUT);
    pinMode(input3F, OUTPUT);
    pinMode(input4F, OUTPUT);
    pinMode(input1B, OUTPUT);
    pinMode(input2B, OUTPUT);
    pinMode(input3B, OUTPUT);
    pinMode(input4B, OUTPUT);

    // Set all pins to low (off)
    digitalWrite(input1F, LOW);
    digitalWrite(input2F, LOW);
    digitalWrite(input3F, LOW);
    digitalWrite(input4F, LOW);
    digitalWrite(input1B, LOW);
    digitalWrite(input2B, LOW);
    digitalWrite(input3B, LOW);
    digitalWrite(input4B, LOW);
}

void loop() {

    Movement::moveForward();
    delay(1000);

    Movement::moveBackward();
    delay(1000);

    Movement::turnLeft();
    delay(1000);

    Movement::turnRight();
    delay(1000);

    Movement::strafeRight();
    delay(1000);

    Movement::strafeLeft();
    delay(1000);

    Movement::stopMovement();
    delay(5000);
}
