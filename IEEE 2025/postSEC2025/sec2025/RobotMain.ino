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

bool isSafeDistanceAway(int sensor) {
  //Read_Multi_Sensors();
  int Offset = 0;
  
  if (sensor == Front_Left || Front_Right){
    Offset = 75;
  }

  if (Sensor[sensor].Distance < (safeDistanceAway + Offset)) {
    return false;
  }
  return true;
}


// I know this should go into its own ino file eventually
bool inPosition = false;
bool hasCaseStarted = false;

bool LocationHelper(int state) {
  switch (state) {
    //should be in the pad 0 corner, sweeper facing a wall
    case 1:
      hasCaseStarted = true;
      inPosition = false;
      // MoveForward();
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      //are front sensors hitting wall?
      //are left sensors hitting wall?
      if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
        if (!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
          inPosition = true;
        }
      }
      //if yes, do the safe rotation adjustment and rotate
      if (inPosition) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;

      //if no, return false (not in position yet)
      break;
    case 2:
      hasCaseStarted = true;
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      //are front sensors hitting wall?
      //are left sensors hitting wall?
      if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
        if (!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
          inPosition = true;
        }
      }
      //if yes, do the safe rotation adjustment and rotate
      if (inPosition) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;
      //if no, return false (not in position yet)
      break;
    case 3:
      //are some of front sensors hitting wall?
      //are left sensors hitting wall?
      //if yes, do the safe rotation adjustment and rotate
      //if no, adjust position until OK to do so
      hasCaseStarted = true;
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;
      break;
    case 4:
      hasCaseStarted = true;
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }
      //facing the south wall
      if (inPosition) {
        Stop();
        SafeRotate("CCW", 90);
        return true;
      }
      return false;
      break;
    case 5:  //WILL REQUIRE TIMED MOVEMENT
      //are right sensors hitting a wall (& no others?)
      hasCaseStarted = true;
      Movement_Adjust("Forward");
      delay(500);
      Stop();
      SafeRotate("CCW", 90);
      return true;
      break;
    case 6:
      //is one (or maybe two) front sensors hitting nebulite box?
      inPosition = false;
      hasCaseStarted = true;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Left)) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;

      break;
    case 7:  //WILL REQUIRE TIMED MOVEMENT
      //no sensors should be hitting anything
      inPosition = false;
      hasCaseStarted = true;
      Movement_Adjust("Forward");
      delay(500);
      Stop();
      SafeRotate("CCW", 90);
      return true;
      break;
    case 8:
      //are one or more left sensors hitting nebulite box?
      ///are front sensors hitting wall?
      inPosition = false;
      hasCaseStarted = true;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Left_Front)) {
        inPosition = true;
      }
      //turn around to face the south wall ( not there yet)
      if (inPosition) {
        Stop();
        SafeRotate("CCW", 180);
        return true;
      }
      return false;
      break;
    case 9:
      //are front sensors hitting wall?
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        SafeRotate("CCW", 90);
        return true;
      }
      return false;
      break;
    case 10:
      //are one or more front sensors hitting geodinium box?
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        SafeRotate("CCW", 90);
        return true;
      }
      return false;
      break;
    case 11:
      //are front sensors hitting wall?
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Front_Left)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;
      break;
    case 12:
      //are front sensors hitting wall?
      //are left sensors hitting wall?
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Front_Left)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;
      break;
    case 13:
      //are front sensors hitting geodinium box?
      //are left sensors hitting wall?
      inPosition = false;
      Movement_Adjust("Forward");
      Read_Multi_Sensors();
      if (!isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Front_Left)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        SafeRotate("CW", 90);
        return true;
      }
      return false;
      break;
  }
}

//TODO: set up sensor reading code to always assign 1000 to distance if out of range
void SafeRotate(String direction, int angle) {
  CheckForWallCollisions();

  angle = delayScalingFactor * angle;

  if (direction == "CW") {
    //rotate CW for x degrees
    RotateCW();
    //figure out how to convert time delay to equivalent rotation angle
    delay(angle);
    Stop();
  } else {
    //rotate CCW for x degrees
    RotateCCW();
    //figure out how to convert time delay to equivalent rotation angle
    delay(angle);
    Stop();
  }
}
