#include <Arduino.h>

#define NUM_LEDS     8

// duration to pause
int delayTime = 1000;

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

void loop()
{
  // Start with all LEDs off
  byte storageByte = 0x00;
  // Keep track of which LED to turn on
  byte newLED = 0x01;
  
  // Loop through all LEDs
  for (int i = 0; i < NUM_LEDS; i++)
  {
    // Add the new LED to the pattern using OR operation
    storageByte = storageByte | newLED;
    
    // Update the display
    updateShiftRegister(storageByte);
    
    // Shift to prepare for next LED
    newLED = newLED << 1;
    
    // Wait before turning on next LED
    delay(delayTime);
  }
  
  // Keep the final pattern (all LEDs on)
  while(true) {
    updateShiftRegister(storageByte);
  }
}


//Written by xyz