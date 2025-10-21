#include <Arduino.h>
#include <Stepper.h>

#include "movement.h"
#include "pins.h"
#include "movement.h"

Movement movement;

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

    movement.moveForward();
    delay(1000);

    movement.moveBackward();
    delay(1000);

    movement.turnLeft();
    delay(1000);

    movement.turnRight();
    delay(1000);

    movement.strafeLeft();
    delay(1000);

    movement.strafeRight();
    delay(1000);

    movement.stopMovement();
    delay(5000);
}