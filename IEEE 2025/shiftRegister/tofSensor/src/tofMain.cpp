#include <Arduino.h>
#include "Global_Int.h"

// duration to pause
int delayTime = 1000;

// the pin connected to the latch pin, RCLK (pin 12 of the shift register)
//    setting the latch LOW will send the 8 bits in storage to the output pins
int latchPin = 25;
// the pin connected to the clock pin, SRCLK (pin 11 of the shift register)
int clockPin = 26;
// the pin connected to the serial data pin, SER (pin 14 of the shift register)
int dataPin = 24;

void setup() {
// initialize all the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}



void loop() {

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

void setID() {
    // Start with all LEDs off
    byte storageByte = 0x00;
    // Keep track of which LED to turn on
    byte newLED = 0x01;
    
    // all reset
    turnAllOff();
    delay(10);
    // all on
    turnAllOn();
  
    delay(10);
  
    // activating LOX1 and resetting LOX2
    turnAllOff();
    delay(10);

    digitalWrite(SHT_LOX1, HIGH);
    delay(10);
  
    // initing LOX1
    if (!lox1.begin(LOX1_ADDRESS)) {
      Serial.println(F("Failed to boot first VL53L0X"));
    }
    delay(10);
  
    // activating LOX2
    digitalWrite(SHT_LOX2, HIGH);
    delay(10);
  
    //initing LOX2
    if (!lox2.begin(LOX2_ADDRESS)) {
      Serial.println(F("Failed to boot second VL53L0X"));
    }
    delay(10);
  
    // activating LOX3
    digitalWrite(SHT_LOX3, HIGH);
    delay(10);
  
    //initing LOX3
    if (!lox3.begin(LOX3_ADDRESS)) {
      Serial.println(F("Failed to boot third VL53L0X"));
    }
    delay(10);
  
    // activating LOX4
    digitalWrite(SHT_LOX4, HIGH);
    delay(10);
  
    //initing LOX4
    if (!lox4.begin(LOX4_ADDRESS)) {
      Serial.println(F("Failed to boot fourth VL53L0X"));
    }
    delay(10);
  
    // activating LOX5
    digitalWrite(SHT_LOX5, HIGH);
    delay(10);
  
    //initing LOX5
    if (!lox5.begin(LOX5_ADDRESS)) {
      Serial.println(F("Failed to boot fith VL53L0X"));
    }
    delay(10);
  
    // activating LOX6
    digitalWrite(SHT_LOX6, HIGH);
    delay(10);
  
    //initing LOX6
    if (!lox6.begin(LOX6_ADDRESS)) {
      Serial.println(F("Failed to boot sixth VL53L0X"));
    }
    delay(10);
  
    // activating LOX7
    digitalWrite(SHT_LOX7, HIGH);
    delay(10);
  
    //initing LOX7
    if (!lox7.begin(LOX7_ADDRESS)) {
      Serial.println(F("Failed to boot seventh VL53L0X"));
    }
    delay(10);
  
    // activating LOX8
    digitalWrite(SHT_LOX8, HIGH);
    delay(10);
  
    //initing LOX8
    if (!lox8.begin(LOX8_ADDRESS)) {
      Serial.println(F("Failed to boot eigth VL53L0X"));
    }
  
    // activating LOX8
    digitalWrite(SHT_LOX9, HIGH);
    delay(10);
  
    //initing LOX8
    if (!lox9.begin(LOX9_ADDRESS)) {
      Serial.println(F("Failed to boot ninth VL53L0X"));
    }
  
    // activating LOX8
    digitalWrite(SHT_LOX10, HIGH);
    delay(10);
  
    //initing LOX8
    if (!lox10.begin(LOX10_ADDRESS)) {
      Serial.println(F("Failed to boot tenth VL53L0X"));
    }
  }
  
  void read_multi_sensors() {
  
    lox1.rangingTest(&measure1, false);    // pass in 'true' to get debug data printout!
    lox2.rangingTest(&measure2, false);    // pass in 'true' to get debug data printout!
    lox3.rangingTest(&measure3, false);    // pass in 'true' to get debug data printout!
    lox4.rangingTest(&measure4, false);    // pass in 'true' to get debug data printout!
    lox5.rangingTest(&measure5, false);    // pass in 'true' to get debug data printout!
    lox6.rangingTest(&measure6, false);    // pass in 'true' to get debug data printout!
    lox7.rangingTest(&measure7, false);    // pass in 'true' to get debug data printout!
    lox8.rangingTest(&measure8, false);    // pass in 'true' to get debug data printout!
    lox9.rangingTest(&measure9, false);    // pass in 'true' to get debug data printout!
    lox10.rangingTest(&measure10, false);  // pass in 'true' to get debug data printout!
  
  
    // print sensor one reading
  
    if (measure1.RangeStatus != 4) {  // if not out of range
      Sensor[Front_Right].Distance = measure1.RangeMilliMeter;
    }
  
    // print sensor two reading
    if (measure2.RangeStatus != 4) {
      Sensor[Front_Left].Distance = measure2.RangeMilliMeter * 1.2;
    }
    // print sensor three reading
    if (measure3.RangeStatus != 4) {
      Sensor[Left_Front].Distance = measure3.RangeMilliMeter;
    }
    // print sensor four reading
    if (measure4.RangeStatus != 4) {
      Sensor[Left_Back].Distance = measure4.RangeMilliMeter;
    }
    Serial.print(F(" "));
    // print sensor five reading
    if (measure5.RangeStatus != 4) {
      Sensor[Back_Left].Distance = measure5.RangeMilliMeter;
    }
    // print sensor six reading
    if (measure6.RangeStatus != 4) {
      Sensor[Back_Right].Distance = measure6.RangeMilliMeter;
    }
    // print sensor seven reading
    if (measure7.RangeStatus != 4) {
      Sensor[Right_Front].Distance = measure7.RangeMilliMeter;
    }
    // print sensor eight reading
    if (measure8.RangeStatus != 4) {
      Sensor[Right_Back].Distance = measure8.RangeMilliMeter;
    }
    // print sensor eight reading
    if (measure9.RangeStatus != 4) {
      Sensor[Under_Front].Distance = measure9.RangeMilliMeter;
    }
    // print sensor eight reading
    if (measure10.RangeStatus != 4) {
      Sensor[Under_Back].Distance = measure10.RangeMilliMeter;
    }
  }
  
  void read_single_sensor(int SensorPointer) {
    switch (SensorPointer) {
      case 0:
        lox1.rangingTest(&measure1, false);  // pass in 'true' to get debug data printout!
        if (measure1.RangeStatus != 4) {     // if not out of range
          Sensor[Front_Right].Distance = measure1.RangeMilliMeter;
        }
        break;
  
      case 1:
        lox2.rangingTest(&measure2, false);  // pass in 'true' to get debug data printout!
        if (measure2.RangeStatus != 4) {     // if not out of range
          Sensor[Front_Left].Distance = measure2.RangeMilliMeter - 12;
        }
        break;
  
      case 2:
        lox3.rangingTest(&measure3, false);  // pass in 'true' to get debug data printout!
        if (measure3.RangeStatus != 4) {     // if not out of range
          Sensor[Left_Front].Distance = measure3.RangeMilliMeter;
        }
        break;
  
      case 3:
        lox4.rangingTest(&measure4, false);  // pass in 'true' to get debug data printout!
        if (measure4.RangeStatus != 4) {     // if not out of range
          Sensor[Left_Back].Distance = measure4.RangeMilliMeter;
        } else {
          Sensor[Left_Back].Distance = 9999;
        }
        break;
  
      case 4:
        lox5.rangingTest(&measure5, false);  // pass in 'true' to get debug data printout!
        if (measure5.RangeStatus != 4) {     // if not out of range
          Sensor[Right_Front].Distance = measure5.RangeMilliMeter;
        }
        break;
  
      case 5:
        lox6.rangingTest(&measure6, false);  // pass in 'true' to get debug data printout!
        if (measure6.RangeStatus != 4) {     // if not out of range
          Sensor[Right_Back].Distance = measure6.RangeMilliMeter;
        }
        break;
  
      case 6:
        lox7.rangingTest(&measure7, false);  // pass in 'true' to get debug data printout!
        if (measure7.RangeStatus != 4) {     // if not out of range
          Sensor[Back_Right].Distance = measure7.RangeMilliMeter;
        } else {
          Sensor[Back_Right].Distance = 9999;
        }
        break;
  
      case 7:
        lox8.rangingTest(&measure8, false);  // pass in 'true' to get debug data printout!
        if (measure8.RangeStatus != 4) {     // if not out of range
          Sensor[Back_Left].Distance = measure8.RangeMilliMeter;
        }
        break;
  
      case 8:
        lox9.rangingTest(&measure9, false);  // pass in 'true' to get debug data printout!
        if (measure9.RangeStatus != 4) {     // if not out of range
          Sensor[Under_Front].Distance = measure9.RangeMilliMeter;
        }
        break;
  
      case 9:
        lox10.rangingTest(&measure10, false);  // pass in 'true' to get debug data printout!
        if (measure10.RangeStatus != 4) {      // if not out of range
          Sensor[Under_Back].Distance = measure10.RangeMilliMeter;
        }
        break;
    }
  }
  void Read_Multi_Sensors() {
  
    read_single_sensor(Front_Left);
    read_single_sensor(Front_Right);
    read_single_sensor(Right_Front);
    read_single_sensor(Right_Back);
    read_single_sensor(Left_Front);
    read_single_sensor(Left_Back);
    read_single_sensor(Back_Right);
    read_single_sensor(Back_Left);
    read_single_sensor(Under_Front);
    read_single_sensor(Under_Back);
  }
  
  void SetupSensors() {
    turnAllOn();
    Serial.println(F("Shutdown pins inited..."));
    turnAllOff();
    Serial.println(F("All in reset mode...(pins are low)"));
    for (int i = 0; i < TotalSensors; i++) {
      String Number[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
      Sensor[i].LOX_ADDRESS = 0x30 + i;
      Sensor[i].Xshut = 22 + i;
      Sensor[i].Name = "Sensor " + Number[i];
    }
    setID();
  }
  
  void turnAllOff() {
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);
    digitalWrite(SHT_LOX3, LOW);
    digitalWrite(SHT_LOX4, LOW);
    digitalWrite(SHT_LOX5, LOW);
    digitalWrite(SHT_LOX6, LOW);
    digitalWrite(SHT_LOX7, LOW);
    digitalWrite(SHT_LOX8, LOW);
    digitalWrite(SHT_LOX9, LOW);
    digitalWrite(SHT_LOX10, LOW);
  }
  
  void turnAllOn() {
    pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);
    pinMode(SHT_LOX3, OUTPUT);
    pinMode(SHT_LOX4, OUTPUT);
    pinMode(SHT_LOX5, OUTPUT);
    pinMode(SHT_LOX6, OUTPUT);
    pinMode(SHT_LOX7, OUTPUT);
    pinMode(SHT_LOX8, OUTPUT);
    pinMode(SHT_LOX9, OUTPUT);
    pinMode(SHT_LOX10, OUTPUT);
  }
  
  