#include "Adafruit_VL53L0X.h"
#include <Servo.h>
#include "Global_Int.h"
/*DEPENDENCIES FROM LAST YEAR: GLOBALINT.H, MOVEMENTFUNCTIONS.INO, SENSORFUNCTIONS.INO*/







//I AM ASSUMING SWEEPER IS ALWAYS FRONT, ALL SENSOR DIRECTIONS RELATIVE TO SWEEPER
//        front (sweeper)
//   @@@@@@@@
// l |      | r
// e |      | i
// f |      | gh
// t |......| t
//     back


//Have no idea if any of this is still necessary
void setup() {
  Serial.begin(115200);



  // wait until serial port opens for native USB devices
  while (!Serial) { delay(1); }
  SetupSensors();
  ServoSetup();

  BrushDock.attach(BrushDock_Pin);
  MoveBrush(true);
  SpinBrush.attach(SpinBrush_Pin);




  Serial.println(F("Starting robot..."));
  //may be necessary to bring this back once the grabbing arm is installed
  //SetupServos();


  // For brush
  EnableSortingSystem(false);
  //(Optional)
}

void loop(){
  Read_Multi_Sensors();
  ReadClosestWall();
  DisplayReadings(1);
}

/*
void loop() {
  EnableSortingSystem(false);
  //spin(true);
  // while(1){
  //    Read_Multi_Sensors();
  //   DisplayReadings(1);
  // }

MoveRight(.5);
delay(250);
Stop();
  while (State <= 2) {
    MoveForward(.5);
    Read_Multi_Sensors();
    DisplayReadings(1);



    if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
      Serial.println("Stopping");
      Stop();
      spin(false);
      RotateCW(.2);
      delay(1700);
      Stop();
      MoveLeft(.5);
      delay(1000);
      MoveRight(.5);
      delay(175);
      MoveBackward(.5);
      delay(1000);
     
      Stop();
      delay(2500);
      State++;
    }
  }
  while (State == 3){
    MoveForward(.5);
    Read_Multi_Sensors();
    DisplayReadings(1);



    if (!isSafeDistanceAway(Front_Left)) {
      Serial.println("Stopping");
      Stop();
      spin(false);
      RotateCW(.2);
      delay(1700);
      Stop();
      MoveBackward(.5);
      delay(1000);
      MoveForward(.5);
      delay(200);
      MoveLeft(.5);
      delay(1000);
      MoveBackward(.2);
      delay(350);
      Stop();
      delay(2500);
      State++;
    }

  }
   while (State == 4) {
    MoveForward(.5);
    Read_Multi_Sensors();
    DisplayReadings(1);



    if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
      Serial.println("Stopping");
      Stop();
      spin(false);
      MoveBackward(.5);
      delay(300);
      RotateCCW(.2);
      delay(1700);
      Stop();
      MoveRight(.5);
      delay(1000);
      MoveRight(.5);
      delay(125);
      MoveForward(.5);
      delay(750);
      RotateCCW(.2);
      delay(1700);
      MoveBackward(.5);
      delay(1000);
      Stop();
      State++;
      delay(99999);
    }
  }












  // while(objective == setupTasks){
  //     //do LED stuff
  //     //when done, set objective to setup
  // }
  // while(objective == sweepOuterField){
  //     //state = 1;
  //     //if state is done executing, move to the next one
  //     //NO SENSORS RN -- UNCOMMENT FOLLOWING LINES WHEN THERE ARE SENSORS
  //     // if(state != 3 && LocationHelper(state)){
  //     //     state++;
  //     // }
  //     // //end prematurely (Honestly dont think I'll even get this far)
  //     // if(state == 3){
  //     //     Stop();
  //     //     return;
  //     // }
  //     // if (LocationHelper(state)){
  //     //     state++;
  //     // }

  //     if(hasMovementStarted){
  //         //tempMovementFn();


  //     }
  // }
  // while(objective == pickUpBoxes){

  // }
  // while(objective == dropOffBlocks){

  // }
  // while(objective == sweepCave){

  // }
  // while(objective == dropOffBlocksFromCave){

  // }
  // while(objective == beacon){

  // }
}
*/

bool isSafeDistanceAway(int sensor) {
  //Read_Multi_Sensors();
  int Offset = 0;
  
  if (sensor == Front_Left || sensor == Front_Right){
    Offset = 75;
  }

  if (Sensor[sensor].Distance < (safeDistanceAway + Offset)) {
    return false;
  }
  return true;
}


