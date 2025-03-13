#include <Arduino.h>
#include "Global_Int.h"
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

void initializeToFSensors() {
  #define NUM_SENSORS 10  // Number of sensors (also number of LEDs)
  
  // the pin connected to the latch pin, RCLK (pin 12 of the shift register)
  //    setting the latch LOW will send the 8 bits in storage to the output pins
  int latchPin = 25;
  // the pin connected to the clock pin, SRCLK (pin 11 of the shift register)
  int clockPin = 26;
  // the pin connected to the serial data pin, SER (pin 14 of the shift register)
  int dataPin = 24;

  // Define sensor addresses
  const int sensorAddresses[NUM_SENSORS] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39
  };

  // Array of VL53L0X sensor objects
  Adafruit_VL53L0X lox[NUM_SENSORS];

  // Start with all sensors off
  byte storageByte = 0x00;
  // Keep track of which sensor  to activate
  byte newSensor = 0x01;

  // Set pins
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  // Initialize each sensor
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Initializing Sensor ");
    Serial.println(i);

    // Add the new sensor to the pattern using OR operation
    storageByte |= newSensor;

    // Turn latch pin off
    digitalWrite(latchPin, LOW);

    // send the storage byte to the shift register with the LSB first
    //     since the latch is LOW, set the 8 output pins based on the stored 8 bits and in turn light the correct LED
    shiftOut(dataPin, clockPin, LSBFIRST, storageByte);

    // set the latch pin HIGH again
    digitalWrite(latchPin, HIGH);

    // Shift to prepare for next sensor
    newSensor <<= 1;

    delay(10);

    if (!lox[i].begin(sensorAddresses[i])) {
        Serial.print("Failed to boot VL53L0X sensor ");
        Serial.println(i);
    } else {
        Serial.print("VL53L0X sensor ");
        Serial.print(i);
        Serial.println(" initialized successfully");
    }

    delay(10);  // Small delay to stabilize each sensor
  }
}