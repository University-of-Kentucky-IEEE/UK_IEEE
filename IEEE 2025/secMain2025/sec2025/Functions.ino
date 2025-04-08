#pragma once
#include "Global_Int.h"


// void Timer(int Period) {  // Use Timer(1); to start timer and Timer(2); to end timer. results will be in Time.RecordedTime
//   if (Period == 1) {
//     Time.temp = millis();
//   } else {
//     Time.RecordedTime = millis() - Time.temp;
//    // Serial.print("Time to Finish ");
//   //  Serial.println(Time.RecordedTime);
//   }
// }

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

    // case 2:
    //   Serial.print(" SideDif ");
    //   Serial.print(SideDif);
    //   Serial.print(" Tilting = ");
    //   Serial.print(SideTilt);
    //   Serial.println();
    //   break;

    // case 3:
    //   Serial.print("Time to run task: ");
    //   Serial.print(Time.RecordedTime);
    //   Serial.print(" milliseconds");
    //   Serial.println();
    //   break;
      
    // case 4:
    //   Serial.print("Current Base Position ");
    //   Serial.print(CurrentBaseAngle);
    //   Serial.print(" degrees");
    //   Serial.println();
    //   break;
  }
}

// light sensor functions

// function to get the avg light level for the period length of seconds. 1000 = 1 sec
int LightAverage(const int pin){
    const unsigned long period = 350;    // period of 1 seconds
  unsigned long lightAvg = 0;
  unsigned long startMillis = millis();
  while(millis() - startMillis < period){ 
    // for 3 seconds, get the analog read of the photoresistor
    lightAvg = lightAvg + analogRead(pin);
  }
  return (lightAvg / period); // return avg per millisecond for now
}

// senses for 5 seconds changes in light levels, then it continues with rest of following robot functions
int SenseLight(const int photoRpin)
{
  // initialize while loop variable and timeout for function
  bool loopFlag = 0;
  const unsigned long period = 10000;  // how long the program will run for max
  unsigned long startMillis = millis(); // time at start of program

  // get first light avg number
  unsigned int prevAvg = LightAverage(photoRpin); // read voltage at pin A0, the photoresistor
  
  // continuously get average light readings and compare them until large difference detected
  // then set loopFlag to 1 or until 5 seconds have passed
  while(millis() - startMillis < period){
    unsigned int curAvg = LightAverage(photoRpin);  // take another average after previous

    //Serial.print("Current: ");
    //Serial.println(curAvg);
    //Serial.print("cur avg need to beat: ");
    
    unsigned int beatVal = 1.2*prevAvg;
    //Serial.println(beatVal);
    if(curAvg >= beatVal){ // if current average is greater than 1.2x prevAvg
      loopFlag = 1;
      break;
    }

    prevAvg = curAvg;   // current becomes previous to compare with next current.
  }
}
