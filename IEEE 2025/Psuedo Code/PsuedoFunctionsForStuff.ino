#include "TOF_Functions"
#include <Servo.h>

//ServoNames
Servo GeodeSorter;
Servo MagneticStorage;
Servo NonMagneticStorage;
Servo BrushDock;
Servo ConveyorBelt;
Servo ShippingGrab;
Servo Sprial;

//Servo Pins
#define GeodeSorter_Pin 1
#define MagneticStorage_Pin 2
#define NonMagneticStorage_Pin 3
#define BrushDock_Pin 4
#define ConveyorBelt_Pin 5
#define Sprial_Pin 6
#define ShippingGrab_Pin 7

void ServoSetup(){
    GeodeSorter.attach(GeodeSorter_Pin);
    SortGeode(false);

    MagneticStorage.attach(MagneticStorage_Pin);
    MagneticStorageContainer(false);

    NonMagneticStorage.attach(NonMagneticStorage_Pin);
    NonMagneticStorageContainer(false);

    BrushDock.attach(BrushDock_Pin);
    
    ConveyorBelt.attach(ConveyorBelt_Pin);

    Sprial.attach(Sprial_Pin);

    ShippingGrab.attach(ShippingGrab_Pin);

}

//
//Designated Servo Functions Functions 
//Use these functions for servos with designated positions
//

void MagneticStorageContainer(bool Open){
    if (Open){                          //Open Magnetic Storage Container
        MagneticStorage.write(90);
    } else {                          //Close Magnetic Storage Container
        MagneticStorage.write(0);
    }
}

void NonMagneticStorageContainer(bool Open){
    if (Open){                          //Open Magnetic Storage Container
        NonMagneticStorage.write(90);
    } else {                          //Close Magnetic Storage Container
        NonMagneticStorage.write(0);
    }
}

void SortGeode(bool magnetic){
    if (magnetic){              //if Magnetic geode is detected
        GeodeSorter.write(0);
    } else {                    //Default sort to non magnetic (NEED TO TEST FOR CORRECT ANGLES)
        GeodeSorter.write(134.7);
    }
}

void GrabShippingContainer(bool Grab){
    if (Grab){              // If we want to grab shipping container
        ShippingGrab.write(0);
    } else {                    //Release
        ShippingGrab.write(135);
    }
}

void MoveBrush(bool InPosition){
    if (InPosition){              //Brush is in position
        BrushDock.write(0);
    } else {                    //Resting Position
        BrushDock.write(135);
    }
}




//
// READ EVERY CODE CYCLE
//
float TimeSinceDetection = 0.0;
void CheckForMagnet(){    //Checks for Magnetic Field 

    int HallEffectReading =  analogRead(A0);
    Serial.print("Hall Sensor Reading = ");
    Serial.print(HallEffectReading);

    if ((HallEffectReading >= 503 && HallEffectReading <= 525) ) { // (value2 >= 495 && value2 <= 505) && (value3 >= 495 && value3 <= 505) && (value4 >= 505 && value4 <= 515)){
        Serial.println("  Magent NOT Detected"); // 

        if ((millis() - TimeSinceDetection) >= 3 ){ //check time since last magnetic detection, reset sorter if xxx seconds passed
            SortGeode(false); 
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
#define MinContainerDistance 50

#define Magnetic 1
#define NonMagnetic 0

int CheckShippingContainerPosition(){ //checks where shipping container is located
    if (Sensor[Back_Right].Distance < MinContainerDistance && Sensor[Back_Left].Distance < MinContainerDistance){          //Container is in MIDDLE of robot , Both back sensors are very close
        return ContainerInMiddle;

    } else if (Sensor[Back_Right].Distance < MinContainerDistance && Sensor[Back_Left].Distance > MinContainerDistance){   //Container is on RIGHT SIDE of robot , Right sensor is close
        return ContainerOnRightSide;

    } else if (Sensor[Back_Right].Distance > MinContainerDistance && Sensor[Back_Left].Distance < MinContainerDistance){   //Container is on LEFT SIDE of robot , Left sensor is close
        return ContainerOnLeftSide;

    } else {                                                                                                               //Container is not close enough or not detected
        return ContainerMissing;
    }
}

void DepositGeodes(bool magnetic){      //ONLY USE IF WE KNOW WHERE SHIPPING CONTAINER IS
    float DepositStartTime = millis(); //Safety Excape incase of inf loop
    bool Deposited = false;
    while (!Deposited){                 //loop until geodes are deposited 
        int CurrentContainerPosition = CheckShippingContainerPosition();
        if (CurrentContainerPosition = ContainerOnRightSide) {                //If Container is on Right Side of Robot
            if (magnetic){
                Stop();
                MagneticStorageContainer(true); // Open Magnetic Container
                delay(5000);                    // wait for geodes to fall
                MagneticStorageContainer(false);
                Deposited = true;
            } else {
                MoveLeft();                     
            }
        } else if (CurrentContainerPosition = ContainerOnLeftSide) {                //If Container is on left Side of Robot
            if (magnetic){
                MoveRight();
            } else {
                Stop();
                NonMagneticStorageContainer(true); // Open Magnetic Container
                delay(5000);                    // wait for geodes to fall
                NonMagneticStorageContainer(false); // Close NonMagnetic Container
                Deposited = true;                 
            }
        } else if (CurrentContainerPosition = ContainerInMiddle) {                //If Container is in middle of Robot
            if (magnetic){
                MoveRight();
            } else {
                MoveLeft();                
            }
        } else {                //LOOK HERE IN CASE OF "SKIPPING" OVER THIS FUNCTION 
            Deposited = true; //FAILED TO FIND SHIPPING CONTAINER BREAK OUT 
        }
        if ((millis()-DepositStartTime) > 15){ // Time limit exceeded DO NOT RELEASE CONTAINER 
            Deposited = true;
        }
    }
}

//Shipping Container information
#define Magnetic 1
#define NonMagnetic 0

typedef struct { //current Known coordinates for shipping container
    int xCoord;
    int yCoord;
    
  } ShippingContainerInformation;
  ShippingContainerInformation ShippingContainer[2];

  //
  //Direction
  //

  #define North 0
  #define East 1
  #define South 2
  #define West 3
 
  #define CW 1
  #define CCW -1

  int Direction = East; //Starting Direction
  int ClosestWall = South;

  void ChangeDirection(int rotation){  //Changes global direction when we rotate, CW is positive direction
    Direction = Direction + rotation;
    Direction = OutputDirection(Direction);
  }

  void OutputDirection(int tempDirection){ //Contrains direction to 0-3
    while (tempDirection > 3 || tempDirection < 0){
        if (tempDirection < North){
            tempDirection += 4;
        }
        if (tempDirection > 3){
            tempDirection -= 4;
        }
    }
    return tempDirection;
  }
  
  
  int GetClosestWall(){ //gets closest wall direction 
    Read_Multi_Sensors();
    int FrontAverage = (Sensor[Front_Left].Distance + Sensor[Front_Right].Distance); //North on robot 0
    int RightAverage = (Sensor[Right_Front].Distance + Sensor[Right_Back].Distance); // East on robot 1
    int BackAverage = (Sensor[Back_Left].Distance + Sensor[Back_Right].Distance);    //South on robot 2
    int LeftAverage = (Sensor[Left_Front].Distance + Sensor[Left_Back].Distance);    //West  on robot 3
    
    int Averages = [FrontAverage, RightAverage, BackAverage, LeftAverage];

    int CloestDirection = North;  //According to robot 

    for (int i = 0; i < 4; i ++){                       //gets side of the robot with the closest side
        if (Averages[i] <= Averages[CloestDirection]){
            CloestDirection = i;
        }
    }
    CloestDirection = OutputDirection(CloestDirection + Direction);
    return CloestDirection;
  }
  

  void SafeRotateCW(){
    bool InPosition = false; 
    while (!InPosition){
        RotateCW();
        read_single_sensor(Direction + 2)
    }
    ChangeDirection(CW);
  }


