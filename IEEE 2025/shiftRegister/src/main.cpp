#include <Arduino.h>

#define NUM_LEDS     8

// duration to pause
int delayTime = 100;

// the pin connected to the latch pin, RCLK (pin 12 of the shift register)
//    setting the latch LOW will send the 8 bits in storage to the output pins
int latchPin = 25;
// the pin connected to the clock pin, SRCLK (pin 11 of the shift register)
int clockPin = 26;
// the pin connected to the serial data pin, SER (pin 14 of the shift register)
int dataPin = 24;


// This code runs once when the program starts, and no more
void setup()
{
  // initialize all the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

// function which sends the stored byte to the output pins by setting the latch pin LOW
void updateShiftRegister(byte storageByte)
{
  // set the latch pin LOW
  digitalWrite(latchPin, LOW);

  // send the storage byte to the shift register with the LSB first
  //     since the latch is LOW, set the 8 output pins based on the stored 8 bits and in turn light the correct LED
  shiftOut(dataPin, clockPin, LSBFIRST, storageByte);

  // set the latch pin HIGH again
  digitalWrite(latchPin, HIGH);
}

// The code in here will run continuously until we turn off the Arduino Dock
void loop()
{
  // the byte (8 bits) to be stored in the shift register
  //    initialize to 00000001, representing the first LED on
  byte storageByte = 0x01;

  // create the effect of having the light travel to the left
  for (int i = 0; i < NUM_LEDS-1; i++)
  {
    // send the 8 bits to the shift register and set latch LOW
    updateShiftRegister(storageByte);

    // bitwise shift to the left by 1 bit
    //    the MSB will disappear and a 0 will be shifted in for the LSB
    //  ex. 10000001 to 00000010
    storageByte = storageByte << 1;

    // wait before moving on to the next LED to enhance the animation
    delay(delayTime);   
  }

  // create the effect of having the light travel in the opposite direction
  for (int i = 0; i < NUM_LEDS-1; i++)
  {
    // send the 8 bits to the shift register and set latch LOW
    updateShiftRegister(storageByte);

    // bitwise shift to the right by 1 bit
    //    the LSB will disappear and a 0 will be shifted in for the MSB
    //     i.e. 10000000 to 01000000
    storageByte = storageByte >> 1;

    // wait before moving on to the next LED to enhance the animation
    delay(delayTime);   
  }
}

//Written by xyz