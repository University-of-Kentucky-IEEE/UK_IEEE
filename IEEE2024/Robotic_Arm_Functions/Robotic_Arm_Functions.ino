//
//
// ROBOTIC ARM FUNCTIONS
//
//
/*

REMINDER FOR IDS

BaseServo_ID 0
ArmBase_ID 1
Elbow1_ID 2
Elbow2_ID 3
Wrist_ID 4
Grabber_ID 5        
FrontCaster_ID 6
BackCaster_ID 7      //Back caster servo
FR_ID 8             //front right servo
BR_ID 9             //back right servo
FL_ID 10            //front left servo
BL_ID 11            //back left servo
*/


void GetBaseAngle() {  //Gets potentiometer angle
  float PotValue = analogRead(A0);
  CurrentBaseAngle = (PotValue) / (2 * 511.5) * MIN_BASE_ANGLE;
  DisplayReadings(4);
}

void TurnBase(float DesiredAngle) {  // turns arm base


  GetBaseAngle();  //Get base angle


  if (DesiredAngle > MAX_BASE_ANGLE) {  //FailSafe in case inputed angle is outside turn radius
    DesiredAngle = MAX_BASE_ANGLE;
  } else if (DesiredAngle < MIN_BASE_ANGLE) {
    DesiredAngle = MIN_BASE_ANGLE;
  }

  float AngleDifference = DesiredAngle - CurrentBaseAngle;
  int TurnDirection = AngleDifference / abs(AngleDifference);

  while ((AngleDifference > 1) || (AngleDifference < -1)) {  //loop while Base angle is not within 2 degrees of desired angle
    if (TurnDirection > 0) {
      BaseServo.writeMicroseconds(MaxPulse);  // rotate base clockwise
    }
    if (TurnDirection < 0) {
      BaseServo.writeMicroseconds(MinPulse);  // rotate base counter clockwise
    }
    GetBaseAngle();
    AngleDifference = DesiredAngle - CurrentBaseAngle;
    TurnDirection = AngleDifference / abs(AngleDifference);
  }
  BaseServo.writeMicroseconds(Stall);
}

void ArmHome() {  //Sets arm into Home Position
  TurnServo(Elbow2, Elbow2_ID, ServoType[Elbow2_ID].MaxAngle, 500);
  TurnServo(Elbow1, Elbow1_ID, ServoType[Elbow1_ID].MaxAngle, 500);
  TurnServo(Wrist, Wrist_ID, ServoType[Wrist_ID].MaxAngle, 500);
  TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MinAngle, 500);
  TurnServo(Elbow2, Elbow2_ID, ServoType[Elbow2_ID].MinAngle, 500);
  TurnServo(PixyCam, PixyCam_ID, 45, 500);
}

void SetupServos() {
  /*
  typedef struct {
  int Pin;
  int CurrentPosition;
  int MinAngle;
  int MaxAngle;
  ServoInfo;
  */
  ServoType[PixyCam_ID] = { 1, 0, 0, 90 };
  ServoType[BaseServo_ID] = { 2, 1500, 500, 2500 };
  ServoType[ArmBase_ID] = { 3, 0, 0, 180 };
  ServoType[Elbow1_ID] = { 4, 0, 0, 180 };
  ServoType[Elbow2_ID] = { 5, 0, 0, 180 };
  ServoType[Wrist_ID] = { 6, 0, 0, 180 };
  ServoType[Grabber_ID] = { 7, 0, 0, 180 };
  ServoType[FrontCaster_ID] = { 8, 0, 0, 180 };
  ServoType[BackCaster_ID] = { 9, 0, 0, 180 };
  ServoType[FR_ID] = { 10, 1500, 500, 2500 };
  ServoType[BR_ID] = { 13, 1500, 500, 2500 };
  ServoType[FL_ID] = { 11, 1500, 500, 2500 };
  ServoType[BL_ID] = { 12, 1500, 500, 2500 };
/*
  PixyCam.attach(ServoType[PixyCam_ID].Pin);
  BaseServo.attach(ServoType[BaseServo_ID].Pin);
  ArmBase.attach(ServoType[ArmBase_ID].Pin);
  Elbow1.attach(ServoType[Elbow1_ID].Pin);
  Elbow2.attach(ServoType[Elbow2_ID].Pin);
  Wrist.attach(ServoType[Wrist_ID].Pin);
  Grabber.attach(ServoType[Grabber_ID].Pin);
  */
  FrontCaster.attach(ServoType[FrontCaster_ID].Pin);
  BackCaster.attach(ServoType[BackCaster_ID].Pin);
  FR.attach(ServoType[FR_ID].Pin);  //front right servo
  BR.attach(ServoType[BR_ID].Pin);  //back right servo
  FL.attach(ServoType[FL_ID].Pin);  //front left servo
  BL.attach(ServoType[BL_ID].Pin);  //back left servo

   TurnServo(BackCaster, BackCaster_ID, 0, 1000);
      TurnServo(FrontCaster, FrontCaster_ID, 180, 1000);
      BaseServo.writeMicroseconds(1480);
}

void PickupObject(int Signature) {
  int ObjectDistance = FindDistance(Signature);
}

void TurnServo(Servo ChosenServo, int ServoID, int DesiredAngle, int Duration) {  //Used to turn a specific servo a certain angle in a desired timeframe. Used to slow servos so they dont fling the robot around
                                                                                  //Code may run into an error if It passes the desired angle on accident. need further testing to confirm

  ServoType[ServoID].CurrentPosition = ChosenServo.read();

  if (DesiredAngle > ServoType[ServoID].MaxAngle) {  //if Desired Angle is larger than Max angle for given servo

    DesiredAngle = ServoType[ServoID].MaxAngle;
    Serial.print("WARNING!!! DESIRED ANGLE LARGER THAN MAX ANGLE OF ");
    Serial.print(ServoType[ServoID].MaxAngle);
    Serial.println(" Degrees!!!");

  } else if (DesiredAngle < ServoType[ServoID].MinAngle) {  //if Desired Angle is less than min angle for given servo

    DesiredAngle = ServoType[ServoID].MinAngle;
    Serial.print("WARNING!!! DESIRED ANGLE SMALLER THAN MIN ANGLE OF ");
    Serial.print(ServoType[ServoID].MaxAngle);
    Serial.println(" Degrees!!!");
  }

  float Tick = (DesiredAngle - ServoType[ServoID].CurrentPosition) / abs(DesiredAngle - ServoType[ServoID].CurrentPosition);
  float Delay = Duration / abs(DesiredAngle - ServoType[ServoID].CurrentPosition);

  while (ServoType[ServoID].CurrentPosition != DesiredAngle) {  //add 1 degree every delay until desired angle is reached

    ServoType[ServoID].CurrentPosition = ChosenServo.read();
    if (ServoType[ServoID].CurrentPosition == DesiredAngle) {  //safety breakout once desired angle is reached
      break;
    }
    ChosenServo.write(ServoType[ServoID].CurrentPosition + Tick);

    delay(Delay);
  }
  ServoType[ServoID].CurrentPosition = ChosenServo.read();
}

void TestServoAngle(Servo ChosenServo) {
  for (int pos = 0; pos <= 180; pos++) {  // sweeps from 0 to 180
    ChosenServo.write(pos);
    delay(15);
    Serial.print("Current angle: ");
    Serial.println(ChosenServo.read());
  }
  delay(1000);

  for (int pos = 180; pos >= 0; pos--) {  // sweeps from 180 to 0
    ChosenServo.write(pos);
    delay(15);
    Serial.print("Current angle: ");
    Serial.println(ChosenServo.read());
  }
}

void FuelTankStorage(int TankNumber, bool Task) {  //Task = false - Storing, Task = true - Placing
  switch (TankNumber) {                            //Angle for each storage container position
    case 0:
      TurnBase(TODO);
      break;

    case 1:
      TurnBase(TODO);
      break;

    case 2:
      TurnBase(TODO);
      break;
  }
}



/*
//ObjectType refers to object width indicated in header
//isFuelTank = True if fuel tank, False if colored block
void GrabPackage(int Signature, bool isFuelTank) {  //Used to turn servos sequentially into certain angles to grab object
  //Read package distance, turn base servo if needed

  //int ObjectDistance = FindDistance(Signature);

  if (isFuelTank) {
    TurnServo(Elbow1, Elbow1_ID, ServoType[Elbow1_ID].MinAngle, 1000);
    TurnServo(Wrist, Wrist_ID, ServoType[Wrist_ID].MinAngle, 1000);
    TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MinAngle, 1000);
    TurnServo(Grabber, Grabber_ID, ServoType[Grabber_ID].MinAngle, 1000);
  } else {
    //Change ArmBase and Elbow1 based on distance
    TurnServo(Elbow1, Elbow1_ID, ServoType[Elbow1_ID].MinAngle, 1000);     //move elbow 1
    TurnServo(Elbow2, Elbow2_ID, ServoType[Elbow2_ID].MinAngle, 1000);     //move elbow 2
    TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MinAngle, 1000);  //move shoulder servo
    TurnServo(Wrist, Wrist_ID, ServoType[Wrist_ID].MaxAngle, 800);         //extend wrist
    //Grab package... indicate object being grabbed
    //Check for sweep values indicated by testing
    switch (Signature) {
      case 0:  //small block
        TurnServo(Grabber, Grabber_ID, ServoType[Grabber_ID].MinAngle, 1000);
        break;

      case 1:  //large block
        TurnServo(Grabber, Grabber_ID, 40, 1000);
        break;
    }
  }
}


void BlockStorage(bool isSmall) {
  //Read package distance, turn base servo as needed based on package type
  //if(isSmall == true) {TurnBase(TODO);}
  //else if(isSmall == false) {TurnBase(TODO);}

  TurnServo(Elbow1, Elbow1_ID, ServoType[Elbow1_ID].MinAngle, 1000);     //move elbow 1
  TurnServo(Elbow2, Elbow2_ID, ServoType[Elbow2_ID].MinAngle, 1000);     //move elbow 2
  TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MinAngle, 1000);  //move shoulder servo
  TurnServo(Wrist, Wrist_ID, 75, 1000);                                  //extend wrist
  TurnServo(Grabber, Grabber_ID, ServoType[Grabber_ID].MaxAngle, 1000);  //drop package
}

void FuelTankStorage(int TankNumber, bool Task) {  //Task = false - Storing, Task = true - Placing
  /*
  switch (TankNumber) {                            //Angle for each storage container position
    case 0:
      TurnBase(TODO);
      break;

    case 1:
      TurnBase(TODO);
      break;

    case 2:
      TurnBase(TODO);
      break;
  }

  //TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MaxAngle, 1000);
  //TurnServo(Wrist, Wrist_ID, 55, 1000);
  //TurnServo(Grabber, Grabber_ID, ServoType[Grabber_ID].MaxAngle, 1000);
}
void BlockStorage(bool isSmall) {
  //Read package distance, turn base servo as needed based on package type
  //if(isSmall == true) {TurnBase(TODO);}
  //else if(isSmall == false) {TurnBase(TODO);}

  TurnServo(Elbow1, Elbow1_ID, ServoType[Elbow1_ID].MinAngle, 1000);     //move elbow 1
  TurnServo(Elbow2, Elbow2_ID, ServoType[Elbow2_ID].MinAngle, 1000);     //move elbow 2
  TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MinAngle, 1000);  //move shoulder servo
  TurnServo(Wrist, Wrist_ID, 75, 1000);                                  //extend wrist
  TurnServo(Grabber, Grabber_ID, ServoType[Grabber_ID].MaxAngle, 1000);  //drop package
}

void FuelTankStorage(int TankNumber, bool Task) {  //Task = false - Storing, Task = true - Placing
  / switch (TankNumber) {                          //Angle for each storage container position
    case 0:
      TurnBase(TODO);
      break;

    case 1:
      TurnBase(TODO);
      break;

    case 2:
      TurnBase(TODO);
      break;
  }
  /

  //TurnServo(ArmBase, ArmBase_ID, ServoType[ArmBase_ID].MaxAngle, 1000);
  //TurnServo(Wrist, Wrist_ID, 55, 1000);
  //TurnServo(Grabber, Grabber_ID, ServoType[Grabber_ID].MaxAngle, 1000);
}
*/