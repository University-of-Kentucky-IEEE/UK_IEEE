//#include "RobotMain.ino"

#include <Servo.h>
//ServoNames


void ServoSetup() {
  GeodeSorter.attach(GeodeSorter_Pin);
  SortGeode(false);

  MagneticStorage.attach(MagneticStorage_Pin);
  MagneticStorageContainer(false);

  NonMagneticStorage.attach(NonMagneticStorage_Pin);
  NonMagneticStorageContainer(false);

  BrushDock.attach(BrushDock_Pin);

  ConveyorBelt.attach(ConveyorBelt_Pin);

  Spiral.attach(Spiral_Pin);
  Spiral.writeMicroseconds(1450);

  ShippingGrab.attach(ShippingGrab_Pin);


  BL.attach(pin_BL);
  BR.attach(pin_BR);
  FL.attach(pin_FL);
  FR.attach(pin_FR);

  SpinBrush.attach(SpinBrush_Pin);

  Beacon.attach(Beacon_Pin);
  Beacon.write(90);
  EnableSortingSystem(false);
}

//
//Designated Servo Functions Functions
//Use these functions for servos with designated positions
//

void MagneticStorageContainer(bool Open) {
  if (Open) {  //Open Magnetic Storage Container
    MagneticStorage.attach(MagneticStorage_Pin);
    MagneticStorage.writeMicroseconds(2200);
    delay(500);
    MagneticStorage.writeMicroseconds(800);
  } else {  //Close Magnetic Storage Container
    MagneticStorage.detach();
    MagneticStorage.writeMicroseconds(1990);
  }
}

void NonMagneticStorageContainer(bool Open) {
  if (Open) {  //Open Magnetic Storage Container
    NonMagneticStorage.attach(NonMagneticStorage_Pin);
    NonMagneticStorage.writeMicroseconds(800);
    delay(500);
    NonMagneticStorage.writeMicroseconds(2200);
  } else {  //Close Magnetic Storage Container
    NonMagneticStorage.detach();
    NonMagneticStorage.writeMicroseconds(1348);
  }
}

void SortGeode(bool magnetic) {
  if (magnetic) {  //if Magnetic geode is detected
    GeodeSorter.writeMicroseconds(868);
  } else {  //Default sort to non magnetic (NEED TO TEST FOR CORRECT ANGLES)
    GeodeSorter.writeMicroseconds(1739);
  }
}

void GrabShippingContainer(bool Grab) {
  if (Grab) {  // If we want to grab shipping container
    ShippingGrab.write(0);
  } else {  //Release
    ShippingGrab.write(135);
  }
}

void MoveBrush(bool InPosition) {
  if (InPosition) {  //Brush is in position
    BrushDock.writeMicroseconds(2200);
  } else {  //Resting Position
    BrushDock.writeMicroseconds(900);
  }
}

void spin(bool active) {
  if (active) {
    SpinBrush.writeMicroseconds(MinPulse);  // TODO: check if this works lol
  } else {
    SpinBrush.writeMicroseconds(Stall);
  }
}


void EnableSortingSystem(bool Status) {
  if (Status) {  //enable Sorting System (ConveyorBelt, Brush, Brush Position, and spiral)
    //MoveBrush(true);
    ConveyorBelt.attach(ConveyorBelt_Pin);
    Spiral.attach(Spiral_Pin);
    ConveyorBelt.writeMicroseconds(1250);
    Spiral.writeMicroseconds(1750);

  } else {
    spin(false);
    ConveyorBelt.detach();
    Spiral.detach();
  }
}




//
// READ EVERY CODE CYCLE
//
float TimeSinceDetection = 0.0;
void CheckForMagnet() {  //Checks for Magnetic Field

  int HallEffectReading = analogRead(A1);
  Serial.print("Hall Sensor Reading = ");
  Serial.print(HallEffectReading);

  if ((HallEffectReading >= 490 && HallEffectReading <= 505)) {  // (value2 >= 495 && value2 <= 505) && (value3 >= 495 && value3 <= 505) && (value4 >= 505 && value4 <= 515)){
    Serial.println("  Magent NOT Detected");                     //
    Serial.print("  Time Since Last Detection ");                //
    Serial.println(millis() - TimeSinceDetection);               //
    if ((millis() - TimeSinceDetection) >= 1500) {               //check time since last magnetic detection, reset sorter if xxx seconds passed
      SortGeode(false);
      Serial.print("  Time Since Last Detection ");   //
      Serial.println(millis() - TimeSinceDetection);  //
    }

  } else {
    TimeSinceDetection = millis();  //capture new time since last detection (will keep recording time if magnet is detected)
    Serial.println("  Magent Detected");
    SortGeode(true);
  }
}



//
// Shipping container functions
//
#define ContainerOnRightSide 1
#define ContainerOnLeftSide 2
#define ContainerInMiddle 3
#define ContainerMissing 4
#define MinContainerDistance 150

#define Magnetic 1
#define NonMagnetic 0

int CheckShippingContainerPosition() {  //checks where shipping container is located
  Read_Side(Back);

  Serial.print("Back Right ");
  Serial.println(Sensor[Back_Right].Distance);
  Serial.print("Back Left ");
  Serial.println(Sensor[Back_Left].Distance);

  if (Sensor[Back_Right].Distance < MinContainerDistance && Sensor[Back_Left].Distance < MinContainerDistance) {  //Container is in MIDDLE of robot , Both back sensors are very close
    Serial.println("Shipping Container is in the middle");
    return ContainerInMiddle;

  } else if (Sensor[Back_Right].Distance < MinContainerDistance && Sensor[Back_Left].Distance > MinContainerDistance) {  //Container is on RIGHT SIDE of robot , Right sensor is close
    Serial.println("Shipping Container is on the right");
    return ContainerOnRightSide;

  } else if (Sensor[Back_Right].Distance > MinContainerDistance && Sensor[Back_Left].Distance < MinContainerDistance) {  //Container is on LEFT SIDE of robot , Left sensor is close
    Serial.println("Shipping Container on the left ");
    return ContainerOnLeftSide;

  } else {  //Container is not close enough or not detected
    Serial.println("Shipping Container is missing!!!");
    return ContainerMissing;
  }
}

void DepositGeodes(bool magnetic) {   //ONLY USE IF WE KNOW WHERE SHIPPING CONTAINER IS
  float DepositStartTime = millis();  //Safety Excape incase of inf loop
  bool Deposited = false;
  int CurrentContainerPosition = CheckShippingContainerPosition();
  while (!Deposited) {  //loop until geodes are deposited
    CurrentContainerPosition = CheckShippingContainerPosition();

    if (CurrentContainerPosition == ContainerOnRightSide) {  //If Container is on Right Side of Robot
      if (magnetic) {
        MoveBackward(.25);
        delay(500);
        Stop();
        MagneticStorageContainer(true);  // Open Magnetic Container
        Serial.println("Depositing Magnetic Geodes ");
        Shake();
        //delay(5000);  // wait for geodes to fall
        MagneticStorageContainer(false);
        Deposited = true;
      } else {
        CurrentContainerPosition = CheckShippingContainerPosition();
        Serial.println("Moving Right ");
        MoveRight(.25);
      }
    } else if (CurrentContainerPosition == ContainerOnLeftSide) {  //If Container is on left Side of Robot
      if (magnetic) {
        CurrentContainerPosition = CheckShippingContainerPosition();
        Serial.println("Moving Left ");
        MoveLeft(.25);
      } else {
        MoveBackward(.25);
        delay(500);
        Stop();
        NonMagneticStorageContainer(true);  // Open Magnetic Container
        Serial.println("Depositing NonMagnetic Geodes ");
        Shake();
        //delay(5000);                         // wait for geodes to fall
        NonMagneticStorageContainer(false);  // Close NonMagnetic Container
        Deposited = true;
      }
    } else if (CurrentContainerPosition == ContainerInMiddle) {  //If Container is in middle of Robot
      if (magnetic) {
        Serial.println("Moving Left ");
        MoveLeft(.25);
      } else {
        Serial.println("Moving Right ");
        MoveRight(.25);
      }
    } else {             //LOOK HERE IN CASE OF "SKIPPING" OVER THIS FUNCTION
      Deposited = true;  //FAILED TO FIND SHIPPING CONTAINER BREAK OUt
      Stop();
    }
    if ((millis() - DepositStartTime) > 15000) {  // Time limit exceeded DO NOT RELEASE CONTAINER
      Deposited = true;
    }
  }
}


void Shake() {  //Shake the Geodes out
  for (int i = 0; i < 25; i++) {
    MoveForward(0.25);
    delay(100);
    MoveBackward(0.25);
    delay(100);
  }
  Stop();
}


//Shipping Container information
#define Magnetic 1
#define NonMagnetic 0

typedef struct {  //current Known coordinates for shipping container
  int xCoord;
  int yCoord;

} ShippingContainerInformation;
ShippingContainerInformation ShippingContainer[2];



//
//Direction
//



void ChangeDirection(int rotation) {  //Changes global direction when we rotate, CW is positive direction
  Direction = Direction + rotation;
  Direction = OutputDirection(Direction);
  if (Debug) {
    Serial.print("Now Facing ");
    Serial.println(Direction);
  }
}

int OutputDirection(int tempDirection) {  //Contrains direction to 0-3
  while (tempDirection > 3 || tempDirection < 0) {
    if (tempDirection < North) {
      tempDirection += 4;
    }
    if (tempDirection > 3) {
      tempDirection -= 4;
    }
  }

  return tempDirection;
}


int GetClosestWall() {           //gets closest wall direction
  int ClosestDirection = North;  //According to robot
  for (int i = 0; i < 4; i++) {  //gets side of the robot with the closest side
    if (Side[i].AvgDist <= Side[ClosestDirection].AvgDist) {
      ClosestDirection = i;
    }
  }

  //ClosestDirection = OutputDirection(ClosestDirection - Direction);  // ClosestWall - Direction

  //x  = Closest Directoin
  //  N E S W
  //N 0 1 2 3
  //E 3 0 1 2
  //S 2 3 0 1   -> z = side on robot Facing nearest Wall   -> ID for closest Side sensors    Sensor1 = ClosestDirection * 2 and Sensor2 = ClosestDirection * 2 + 1
  //W 1 2 3 0
  //y = RobotFacing

  return ClosestDirection;
}

//   N   E   S   W
//N 0	1	2	3	4	5	6	7
//E 6	7	0	1	2	3	4	5       Sensor Pins for each direction (same axis as above)
//S 4	5	6	7	0	1	2	3
//W 2 3 4	5	6	7	0	1



void ReadClosestWall() {  //Output Side needed to rotate
  int ClosestDirection = GetClosestWall();
  Serial.print("Reading Closest Side ");
  Serial.println(OutputSideName(ClosestDirection));
  Read_Side(ClosestDirection);
}



void CheckForTurn(int rotation) {
  CheckForWallCollisions();
  Stop();
  bool InPosition = false;
  Read_Multi_Sensors();
  int ClosestWall = GetClosestWall();
  int DistanceDiffFronWall = 0;
  switch (rotation) {
    case CW:
      Serial.println("Rotating CW");
      ClosestWall = OutputDirection(ClosestWall - 1);  //Sensors that will reach the closest wall next
      RotateCW(0.2);
      break;

    case CCW:
      ClosestWall = OutputDirection(ClosestWall + 1);  //Sensors that will reach the closest wall next
      Serial.println("Rotating CCW");
      RotateCCW(0.2);
  }

  delay(1700);
  ReadClosestWall();
  int PreviousSideDif = Side[ClosestWall].SideDif;

  while (!InPosition) {
    PreviousSideDif = Side[ClosestWall].SideDif;
    ReadClosestWall();

    Serial.print("DistanceDiffFronWall ");
    Serial.println(Side[ClosestWall].SideDif);

    if (Side[ClosestWall].SideDif < 50 || (PreviousSideDif > Side[ClosestWall].SideDif)) {  // stops turning if the dif is getting larger or if dif is small enough
      Serial.println("Fully Turned");
      Stop();
      delay(2500);
    }
  }

  ChangeDirection(rotation);
}

void RamWall(int Direction){
  AdjustDistance(Direction,0.5);  //Move into wall
  delay(1000);
  AdjustDistance(OutputDirection(Direction + 2), 0.5); //Move Away From Wall 
  delay(250);
  Stop();
}

#define LineMoveTolerance 25    //Within Line Tolerance

void LineMove(int ReadSide, int DesiredDistance, float Speed) {  //When Going Straight and Movement Adjust Doesnt work, look at the sensors perpendicular to our movement and move to fit within the distance
  Read_Side(ReadSide);
  if (Side[ReadSide].AvgDist < DesiredDistance - LineMoveTolerance) {
    AdjustDistance(OutputDirection(ReadSide + 2), Speed);
    delay(100);
  } else if (Side[ReadSide].AvgDist > DesiredDistance + LineMoveTolerance && Side[ReadSide].AvgDist < 700) {
    AdjustDistance(ReadSide, Speed);
    delay(100);
  } else {
    Serial.println("Distance too far to read, Line Move will not change robot movement ");
  }
}



void CheckForWallCollisions() {
  Read_Side(Front);
  if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
    MoveBackward(.2);
    while (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
      Read_Side(Front);
      // read_single_sensor(Front_Left);   //May not need to remeasure if it does it already in the while loop
      // read_single_sensor(Front_Right);  //how resource intensive is this? will re-reading take too long?
    }
    Stop();
  }
  Read_Side(Left);
  //if left sensors in range, move right until safe distance away
  if (!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
    MoveRight(.2);
    while (!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
      Read_Side(Left);
      // read_single_sensor(Left_Front);  //May not need to remeasure if it does it already in the while loop
      // read_single_sensor(Left_Back);   //how resource intensive is this? will re-reading take too long?
    }
    Stop();
  }
  Read_Side(Right);
  //if right sensors in range, move left until safe distance away
  if (!isSafeDistanceAway(Right_Front) || !isSafeDistanceAway(Right_Back)) {
    MoveLeft(.2);
    while (!isSafeDistanceAway(Right_Front) || !isSafeDistanceAway(Right_Back)) {
      Read_Side(Right);
      // read_single_sensor(Right_Front);  //May not need to remeasure if it does it already in the while loop
      // read_single_sensor(Right_Back);   //how resource intensive is this? will re-reading take too long?
    }
    Stop();
  }
  Read_Side(Back);
  //if back sensors in range, move forward until safe distance away
  if (!isSafeDistanceAway(Back_Left) || !isSafeDistanceAway(Back_Right)) {
    MoveForward(.2);
    while (!isSafeDistanceAway(Back_Left) || !isSafeDistanceAway(Back_Right)) {
      Read_Side(Back);
      // read_single_sensor(Back_Left);   //May not need to remeasure if it does it already in the while loop
      // read_single_sensor(Back_Right);  //how resource intensive is this? will re-reading take too long?
    }
    Stop();
  }
}
