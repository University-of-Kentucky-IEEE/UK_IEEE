#include "Adafruit_VL53L0X.h"
#include "Global.h"
#include <Servo.h>
#define setupTasks 0
#define sweepOuterField 1
#define pickUpBoxes 2
#define dropOffBlocks 3
#define sweepCave 4
#define dropOffBlocksFromCave 5
#define beacon 6
Servo FR;  //front right servo
Servo BR;  //back right servo
Servo FL;  //front left servo
Servo BL;  //back left servo
Servo GeodeSorter;
Servo MagneticStorage;
Servo NonMagneticStorage;
Servo BrushDock;
Servo ConveyorBelt;
Servo ShippingGrab;
Servo Spiral;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (!Serial) { delay(1); }
  SetupSensors();
  ServoSetup();
  Serial.println(F("Starting robot..."));
}

bool hasMovementStarted = true;
int objective = setupTasks;

void loop(){


    while(objective == setupTasks){
        //do LED stuff
        //when done, set objective to setup
        Read_Multi_Sensors();
        //tempMovementFn();


    }
    while(objective == sweepOuterField){
        //state = 1;
        //if state is done executing, move to the next one
        //NO SENSORS RN -- UNCOMMENT FOLLOWING LINES WHEN THERE ARE SENSORS
        // if(state != 3 && LocationHelper(state)){
        //     state++;
        // }
        // //end prematurely (Honestly dont think I'll even get this far)
        // if(state == 3){
        //     Stop();
        //     return;
        // }
        
        if(hasMovementStarted){
         
            
        }
    }
    while(objective == pickUpBoxes){

    }
    while(objective == dropOffBlocks){

    }
    while(objective == sweepCave){

    }
    while(objective == dropOffBlocksFromCave){

    }
    while(objective == beacon){

    }
}

// STATE 1: DISCOVERING GEODINIUM BOX
//unless otherwise stated, directions are WRT orientation of field and not robot
//start: move slightly forward (sweeper is already oriented towards box to prevent blocks getting stuck)
//drive right until hitting geodinium box
    //determine coordinates & orientation using this checkpoint
//drive slightly left to allow for room to rotate
//rotate CCW 90 degrees
//drive slightly right until hitting box again
//grab the box
//looks like we may not be able to assume there are no blocks on landing pad
//will need to sweep landing pad to pick up blocks first
//STATE 2: MOVING GEODINIUM BOX
//move slightly left to give room to rotate box
//rotate CCW 180 degrees
//drive left until hitting wall & corner near pad 0
    //determine coordinates & orientation using this checkpoint
//drop the box
//TODO: we need logic to decide where to put the boxes (i.e. which april tag to garget)
//move right exactly robot + x distance (backwards) where x is a small distance to allow room to maneuver
//rotate CW 90 degrees to orient sweeper in front of robot
//drive forwards until sensors on LEFT side of robot (assuming normal orientation is sweeper forward) detect box on the left
//drive left, pushing box until it hits the wall (how to determine box has hit wall and to stop pushing?)
    //ideally, we are now box units away from the left side of the field
//drive forward until front sensors (sweeper end) detect wall and right sensors (grabber side)
//grab the nebulite box
//move backwards slightly to allow room for rotation
//rotate CW 180 degrees to place the box near the location of pad 4
//drop the box (sweeper is facing)

//attempt 2 this time clearing off the landing pad first
//using cardinal directions this time to make more sense
/********************************************************************** */
//SWEEPING NON-CAVE AREA
//STATE 1:
//move slightly north
//move west until sweeper is in corner of pad 0
//move slightly east to allow room to rotate
//rotate CW 90 until sweeper facing north
//STATE 2:
//move north until sweeper in corner of pad 4
//might be nice to write a function that uses sensor distance from wall to determine how far to adjust
    //before rotation
//move slightly east to allow to rotate
//move slightly south to allow to rotate
//rotate 90 CW (sweeper facing east)
//STATE 3:
//move east until sweeper hits nebulite box
//move slightly west to allow to rotate
//rotate 90 CW (sweeper facing south)
//STATE 4:
//move south until hitting wall (in between pad 0 and landing site)
//move slightly north to allow for rotation
//rotate CCW 90 (sweeper facing east)
//STATE 5:
//move forward x units (length of one side of nebulite box)
//rotate CCW 90 (sweeper facing north)
//STATE 6:
//move north until sweeper hitting nebulite box
//move south slightly to allow to rotate
//rotate CW 90 (sweeper facing east)
//STATE 7:
//move east until robot no longer overlaps with nebulite box (idk distance)
//rotate CCW 90 (sweeper facing north)
//STATE 8:
//move north until sweeper hits wall, sensors on westward facing side of robot detecting nebulite box corner
//move south & east slightly to allow to rotate
//rotate 180 CCW (sweeper facing south)
//STATE 9:
//move south until sweeper hits wall
//move north slightly
//rotate 90 CCW (sweeper facing east)
//STATE 10:
//move east until sweeper hits walls of geodinium container
//move slightly west
//rotate CCW 90 (sweeper facing north)
//STATE 11:
//move north until sweeper hits wall
//move slightly south
//rotate 90 CW (sweeper facing east)
//STATE 12:
//move east until sweeper hits top right corner
//move slightly west and south
//rotate 90 CW (sweeper facing south)
//STATE 13:
//move south until