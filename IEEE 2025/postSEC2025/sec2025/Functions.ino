


// void Timer(int Period) {  // Use Timer(1); to start timer and Timer(2); to end timer. results will be in Time.RecordedTime
//   if (Period == 1) {
//     Time.temp = millis();
//   } else {
//     Time.RecordedTime = millis() - Time.temp;
//    // Serial.print("Time to Finish ");
//   //  Serial.println(Time.RecordedTime);
//   }
// }



// light sensor functions

// function to get the avg light level for the period length of seconds. 1000 = 1 sec
int LightAverage(const int pin) {
  const unsigned long period = 350;  // period of 1 seconds
  unsigned long lightAvg = 0;
  unsigned long startMillis = millis();
  while (millis() - startMillis < period) {
    // for 3 seconds, get the analog read of the photoresistor
    lightAvg = lightAvg + analogRead(pin);
  }
  return (lightAvg / period);  // return avg per millisecond for now
}

// senses for 5 seconds changes in light levels, then it continues with rest of following robot functions
int SenseLight(const int photoRpin) {
  // initialize while loop variable and timeout for function
  bool loopFlag = 0;
  const unsigned long period = 10000;    // how long the program will run for max
  unsigned long startMillis = millis();  // time at start of program

  // get first light avg number
  unsigned int prevAvg = LightAverage(photoRpin);  // read voltage at pin A0, the photoresistor

  // continuously get average light readings and compare them until large difference detected
  // then set loopFlag to 1 or until 5 seconds have passed
  while (millis() - startMillis < period) {
    unsigned int curAvg = LightAverage(photoRpin);  // take another average after previous

    //Serial.print("Current: ");
    //Serial.println(curAvg);
    //Serial.print("cur avg need to beat: ");

    unsigned int beatVal = 1.2 * prevAvg;
    //Serial.println(beatVal);
    if (curAvg >= beatVal) {  // if current average is greater than 1.2x prevAvg
      loopFlag = 1;
      break;
    }

    prevAvg = curAvg;  // current becomes previous to compare with next current.
  }
}
// void tempMovementFn() {
//   hasMovementStarted = false;
//   while (isSafeDistanceAway(Front_Right) && isSafeDistanceAway(Front_Left)) {
//     Movement_Adjust("Forward");
//   }
//   while (isSafeDistanceAway(Front_Right) && isSafeDistanceAway(Front_Left)) {
//     Movement_Adjust("Forward");
//   }
//   Stop();
//   SafeRotate("CW", 90);
//   Stop();
// }

// void brush(bool on) {
//   analogWrite(1, 100);  //ENA  pin
//   analogWrite(0, 200);  //ENB pin
//   if (on) {
//     digitalWrite(motor1pin1, HIGH);
//     digitalWrite(motor1pin2, LOW);
//   } else {
//     digitalWrite(motor1pin1, LOW);
//     digitalWrite(motor1pin2, LOW);
//   }
// }

// void move(bool movement_adjust) {
//   if (movement_adjust) {
//     Movement_Adjust("Forward");
//   } else {
//     MoveForward();
//   }
// }