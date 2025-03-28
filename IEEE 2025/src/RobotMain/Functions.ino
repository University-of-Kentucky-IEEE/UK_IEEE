#pragma once
#include "Global_Int.h"


void Timer(int Period) {  // Use Timer(1); to start timer and Timer(2); to end timer. results will be in Time.RecordedTime
  if (Period == 1) {
    Time.temp = millis();
  } else {
    Time.RecordedTime = millis() - Time.temp;
   // Serial.print("Time to Finish ");
  //  Serial.println(Time.RecordedTime);
  }
}

void DisplayReadings(int Pointer) {  //Displays reading (for degbugging and testing functions) reduces clutter in code and time to run commands
  switch (Pointer) {
    case 1:

      Serial.print(F("FrontL:"));
      Serial.println(Sensor[Front_Left].Distance);
      Serial.print(F("FrontR:"));
      Serial.println(Sensor[Front_Right].Distance);
      Serial.print(F("LeftFront: "));
      Serial.println(Sensor[Left_Front].Distance);
      Serial.print(F("LeftBack:"));
      Serial.println(Sensor[Left_Back].Distance);
      Serial.print(F("BackL:"));
      Serial.println(Sensor[Back_Left].Distance);
      Serial.print(F("BackR:"));
      Serial.println(Sensor[Back_Right].Distance);
      Serial.print(F("RightF:"));
      Serial.println(Sensor[Right_Front].Distance);
      Serial.print(F("RightBack:"));
      Serial.println(Sensor[Right_Back].Distance);
      Serial.print(F("Bottom Front:"));
      Serial.println(Sensor[Under_Front].Distance);
      Serial.print(F("Bottom Back:"));
      Serial.println(Sensor[Under_Back].Distance);
      Serial.println();
      break;

    case 2:
      Serial.print(" SideDif ");
      Serial.print(SideDif);
      Serial.print(" Tilting = ");
      Serial.print(SideTilt);
      Serial.println();
      break;

    case 3:
      Serial.print("Time to run task: ");
      Serial.print(Time.RecordedTime);
      Serial.print(" milliseconds");
      Serial.println();
      break;
      
    case 4:
      Serial.print("Current Base Position ");
      Serial.print(CurrentBaseAngle);
      Serial.print(" degrees");
      Serial.println();
      break;
  }
}

int LightAverage(const int pin){
  const unsigned long period = 1000;    // period of 1 seconds
  unsigned long lightAvg = 0;
  unsigned long startMillis = millis();
  while(millis() - startMillis < period){ 
    // for 3 seconds, get the analog read of the photoresistor
    lightAvg = lightAvg + analogRead(pin);
  }
  return (lightAvg / period); // return avg per millisecond for now
  // issue where the value return is not quite an expected average but it works
}

/*  Useless but can be used as reference
void AdjustServo(Servo Tester, int ServoID, int SideDif) {  //Test code for rotating a servo based on sensor tilt
  int ChangePosition = map(SideDif, -300, 300, 500, 2500);
  Tester.write(ChangePosition);
  ServoType[ServoID].CurrentPosition = Tester.read();
}

*/