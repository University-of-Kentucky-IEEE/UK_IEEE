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

void DepositGeodes(bool magnetic){
    if (magnetic) {                 //deposit on magnetic Side (Right)
        
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