// robot moves 15 cm in 1000 t 

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


    Serial.println(enableA);

   // delay(1000);

    //working code starts



// BUTTON!!! PRESSING START
    moveBackward();
    delay(4280);

     moveForward();
    delay(1000);

    moveBackward();
    delay(1100);

    moveForward();
    delay(1000);

     moveBackward();
    delay(1100);

     moveForward();
    delay(1000);

    moveBackward();
    delay(1100);

    // BUTTON PRESSING END

    moveForward();
    delay(50);

    turnRight();
    delay(1350);

    // turnRight();
    // delay(1300);

    turnLeft();
    delay(50);

    moveForward();
    delay(3000);

    moveBackward();
    delay(1100);

//First duck is now in


    turnLeft();
    delay(1450);
    //delay(1550);

    // moveForward();
    // delay(3930);

    
    moveForward();
    delay(3930);

    turnRight();
    delay(2000);

    moveBackward();
    delay(1100);

    //moveForward();
    //delay(3200);

    // second duck is now captured

    // god awful slow ass turn start

   // turnRight();
    //delay(1000);

    //moveForward();
    //delay(2000);

    //turnRight();
    //delay(1000);

    //moveForward();
    //delay(1000);

    
// god awful slow ass turn

   


    // turnRight();
    // delay(1000);

    stopMovement();
}
void loop() {}