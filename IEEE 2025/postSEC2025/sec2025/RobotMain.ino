#include "Adafruit_VL53L0X.h"

/*DEPENDENCIES FROM LAST YEAR: GLOBALINT.H, MOVEMENTFUNCTIONS.INO, SENSORFUNCTIONS.INO*/
#include "Global_Int.h"
#include <Servo.h>

/*I KNOW THIS IS MESSY AND BADLY ORGANIZED. BEAR WITH ME.*/
//define objectives
#define setupTasks 0
#define sweepOuterField 1
#define pickUpBoxes 2
#define dropOffBlocks 3
#define sweepCave 4
#define dropOffBlocksFromCave 5
#define beacon 6
//tasks to do inside each objective
int state = 1;
//objectives to complete (change this to setupTasks later)
int objective = sweepOuterField;

//integer definitions for the brush
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

//I AM ASSUMING SWEEPER IS ALWAYS FRONT, ALL SENSOR DIRECTIONS RELATIVE TO SWEEPER
//        front (sweeper)
//   @@@@@@@@
// l |      | r
// e |      | i
// f |      | gh
// t |......| t
//     back

//figure out the distance away from wall to safely rotate without hitting it
#define safeDistanceAway 50
//figure out the factor which converts angle degrees to delay time while rotating
#define delayScalingFactor 22.388


//Have no idea if any of this is still necessary
void setup() {
  Serial.begin(115200);
  BaseServo.attach(11);


  // wait until serial port opens for native USB devices
  while (!Serial) { delay(1); }
  SetupSensors();
  ServoSetup();



  Serial.println(F("Starting robot..."));
  //may be necessary to bring this back once the grabbing arm is installed
  //SetupServos();
  BL.attach(pin_BL);
  FL.attach(pin_FL);
  BR.attach(pin_BR);
  FR.attach(pin_FR);

  // For brush

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  //pinMode(motor2pin1, OUTPUT);
  //pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  delay(5000);

  //(Optional)
}

bool hasMovementStarted = true;
void tempMovementFn() {
  hasMovementStarted = false;
  while (isSafeDistanceAway(Front_Right) && isSafeDistanceAway(Front_Left)) {
    Movement_Adjust("Forward");
  }
  while (isSafeDistanceAway(Front_Right) && isSafeDistanceAway(Front_Left)) {
    Movement_Adjust("Forward");
  }
  Stop();
  SafeRotate("CW", 90);
  Stop();
}

void brush(bool on) {
  analogWrite(1, 100);  //ENA  pin
  analogWrite(0, 200);  //ENB pin
  if (on) {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
  } else {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
  }
}
void move(bool movement_adjust) {
  if (movement_adjust) {
    Movement_Adjust("Forward");
  } else {
    MoveForward();
  }
}
float TimeSinceLastState = 0.0;
int State = 1;
bool useMovementAdjust = false;
void loop() {
  /*
  brush(true);
  delay(5000);
  brush(false);
  delay(5000);
  */
  // MoveBrush(true);
  // delay(2000);
  // MoveBrush(false);
  // delay(1000);
  // brush(true);
  // delay(50000);
  // MoveForward();
  // delay(1000);
  // MoveBackward();
  // delay(1000);
  // MoveLeft();
  // delay(1000);
  // MoveRight();
  // delay(1000);
  // Stop();
  // delay(1000);

  // light sensor

  // MagneticStorageContainer(true);
  // NonMagneticStorageContainer(true);
  // delay(250);
  // SenseLight(photoRpin);
  // MoveBrush(false);
  // delay(1000);

while (true){


 CheckForMagnet();
  switch (State) {
    case (0):
      SenseLight(photoRpin);
      State += 1;
      break;

    case 1:
      MoveBrush(true);
      delay(1000);
      spin(true);
      EnableSortingSystem(true);
      State += 1;
      TimeSinceLastState = millis();
      MoveRight();
      delay(1000);
      break;

    case 2:
    MoveForward();
    CheckForMagnet();
    if (millis()-TimeSinceLastState >= (3928.52 )){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

    case 3:
    CheckForMagnet();
    RotateCCW();
    if (millis()-TimeSinceLastState >= 1000){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

    case 4:
    CheckForMagnet();
    MoveForward();
    if (millis()-TimeSinceLastState >= (3428.43 / 2)){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

    case 5:
    CheckForMagnet();
    RotateCCW();
    if (millis()-TimeSinceLastState >= (2000)){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

     case 6:
     CheckForMagnet();
    MoveForward();
    if (millis()-TimeSinceLastState >= (3231.382)){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

    case 7:
    CheckForMagnet();
    RotateCW();
    if (millis()-TimeSinceLastState >= (2000)){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

     case 8:
     CheckForMagnet();
    MoveBackward();
    if (millis()-TimeSinceLastState >= (3231.38 / 2)){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

    case 9:
    CheckForMagnet();
    RotateCCW();
    if (millis()-TimeSinceLastState >= (3231.38 )){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

    case 10:
    CheckForMagnet();
    MoveForward();
    if (millis()-TimeSinceLastState >= (3231.38 )){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

     case 11:
     CheckForMagnet();
    RotateCCW();
    if (millis()-TimeSinceLastState >= (3231.38 )){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

     case 12:
     CheckForMagnet();
    MoveForward();
    if (millis()-TimeSinceLastState >= (3231.38 / 2)){
      TimeSinceLastState = millis();
      State += 1;
    }
    break;

     case 13:
    Stop();
    while(1){}
 
    break;
    
  }
  



}
  // Spiral.writeMicroseconds(MaxPulse);
  // delay(250);
  // ConveyorBelt.writeMicroseconds(MinPulse);
  // delay(1000);

  // move(useMovementAdjust);
  // delay(3928.51 / 2);
  // Stop();
  // delay(500);
  // RotateCCW();
  // delay(75);
  // Stop();
  // delay(500);

  // RotateCW();
  // delay(1450);
  // move(useMovementAdjust);
  // delay(9428.43 / 2);
  // RotateCCW();
  // delay(75);
  // Stop();
  // delay(500);

  // RotateCW();
  // delay(1450);
  // move(useMovementAdjust);
 










  // MagneticStorageContainer(true);
  // delay(100);
  // MagneticStorageContainer(false);
  // delay(100);

  // NonMagneticStorageContainer(true);
  // delay(100);

  // NonMagneticStorageContainer(false);
  // delay(100);

  // GrabShippingContainer(true);
  // delay(100);
  // GrabShippingContainer(false);




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
  if (Sensor[sensor].Distance < safeDistanceAway) {
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

//TODO: set up sensor reading code to always assign 9999 to distance if out of range
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
