#include "lightsensor.h"

int SenseLight(const int photoRpin)
{
  // initialize infinite while loop variable
  bool loopFlag = 0;

  // get first light avg number
  unsigned int prevAvg = LightAverage(photoRpin); // read voltage at pin A0, the photoresistor
  
  // continuously get average light readings and compare them until large difference detected
  // then set loopFlag to 1
  while(true){
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