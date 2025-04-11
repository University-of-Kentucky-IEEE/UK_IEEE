#include "Adafruit_VL53L0X.h"
#include <Servo.h>
/*DEPENDENCIES FROM LAST YEAR: GLOBALINT.H, MOVEMENTFUNCTIONS.INO, SENSORFUNCTIONS.INO*/


Servo BL;
Servo BR;
Servo FR;
Servo FL;


#define TotalSensors 8

#define Front_Right 0
#define Front_Left 1
#define Right_Front 2
#define Right_Back 3
#define Back_Right 4
#define Back_Left 5
#define Left_Front 6
#define Left_Back 7

//TOF information
typedef struct {
  int LOX_ADDRESS;
  int Xshut;
  int Distance;
  String Name;
} SensorData;

#define Front 0
#define Right 1
#define Back 2
#define Left 3

typedef struct {
  int AvgDist;
  int SideDif;   //Left - Right
  //Sensor Side is based on if you were in the middle of the robot and looking at the side
  int LDist;     //Left Sensor Distance
  int RDist;     //Right Sensor Distance
} SideDistance;

SideDistance Side[4];


SensorData Sensor[TotalSensors];

Servo GeodeSorter;
Servo MagneticStorage;
Servo NonMagneticStorage;
Servo BrushDock;
Servo ConveyorBelt;
Servo ShippingGrab;
Servo Spiral;
Servo SpinBrush;
Servo Beacon;



//Servo Pins
#define GeodeSorter_Pin 4
#define MagneticStorage_Pin 2
#define NonMagneticStorage_Pin 3
#define BrushDock_Pin 8
#define ConveyorBelt_Pin 5
#define Spiral_Pin 6
#define ShippingGrab_Pin 7
#define SpinBrush_Pin 14
#define Beacon_Pin 17

#define pin_FR 10
#define pin_FL 9
#define pin_BR 11
#define pin_BL 12



/*I KNOW THIS IS MESSY AND BADLY ORGANIZED. BEAR WITH ME.*/
//define objectives
#define setupTasks 0
#define sweepOuterField 1
#define pickUpBoxes 2
#define dropOffBlocks 3
#define sweepCave 4
#define dropOffBlocksFromCave 5
#define beacon 6

#define North 0
#define East 1
#define South 2
#define West 3

#define CW 1
#define CCW -1

//tasks to do inside each objective
int state = 1;

//objectives to complete (change this to setupTasks later)
int objective = sweepOuterField;

bool hasMovementStarted = true;

float TimeSinceLastState = 0.0;
int State = 1;
bool useMovementAdjust = false;


int Direction = East;  //Direction Robot is facing
int ClosestWall = South;




//I AM ASSUMING SWEEPER IS ALWAYS FRONT, ALL SENSOR DIRECTIONS RELATIVE TO SWEEPER
//        front (sweeper)
//   @@@@@@@@
// l |      | r
// e |      | i
// f |      | gh
// t |......| t
//     back

//figure out the distance away from wall to safely rotate without hitting it
#define safeDistanceAway 150
//figure out the factor which converts angle degrees to delay time while rotating
#define delayScalingFactor 19