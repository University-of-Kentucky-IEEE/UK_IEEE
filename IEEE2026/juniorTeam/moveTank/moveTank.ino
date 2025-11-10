#include <Arduino.h>
#include <Stepper.h>
#include "pins.h"
#include "movement.h"

void setup() {
    Serial.begin(9600);
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
    Serial.println(enableA);

//    moveForward();
//    delay(1000);

   moveBackward();
   delay(1000);

    // turnLeft();
    // delay(1000);

    // turnRight();
    // delay(1000);

    stopMovement();
}