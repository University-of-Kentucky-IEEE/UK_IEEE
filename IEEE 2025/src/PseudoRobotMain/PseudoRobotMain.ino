/*DEPENDENCIES FROM LAST YEAR: GLOBALINT.H, MOVEMENTFUNCTIONS.INO, SENSORFUNCTIONS.INO*/
#pragma once
#include "Global_Int.h"


/*I KNOW THIS IS MESSY AND BADLY ORGANIZED. BEAR WITH ME.*/

//tasks to do inside each objective
int state = 1;
//objectives to complete
int objective = -1;
//define objectives
#define setup 0
#define sweepOuterField 1
#define pickUpBoxes 2
#define dropOffBlocks 3
#define sweepCave 4
#define dropOffBlocksFromCave 5
#define beacon 6
//I AM ASSUMING SWEEPER IS ALWAYS FRONT, ALL SENSOR DIRECTIONS RELATIVE TO SWEEPER
//        front (sweeper)
        //   @@@@@@@@
        // l |      | r
        // e |      | i
        // f |      | gh
        // t |......| t
        //     back

//figure out the distance away from wall to safely rotate without hitting it
#define safeDistanceAway 1

bool isSafeDistanceAway(int sensor){
    if(Sensor[sensor].Distance < safeDistanceAway){
        return false;
    }
    return true;
}

// I know this should go into its own ino file eventually
bool LocationHelper(int state){
    switch(state){
        //should be in the pad 0 corner, sweeper facing a wall
        case 1:
            bool inPosition = false;
            MoveForward();
            Read_Multi_Sensors();
            //are front sensors hitting wall?
            //are left sensors hitting wall?
            if(!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)){
                if(!isSafeDistanceAway(Left_Front) && !isSafeDistanceAway(Left_Back)){
                    inPosition = true;
                }
            }
            //if yes, do the safe rotation adjustment and rotate
            if(inPosition){
                Stop();
                SafeRotate('CW', 90);
                return true;
            }
            return false;
            //if no, return false (not in position yet)
            break;
        case 2:
            bool inPosition = false;
            MoveForward();
            Read_Multi_Sensors();
            //are front sensors hitting wall?
            //are left sensors hitting wall?
            if(!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)){
                if(!isSafeDistanceAway(Left_Front) && !isSafeDistanceAway(Left_Back)){
                    inPosition = true;
                }
            }
            //if yes, do the safe rotation adjustment and rotate
            if(inPosition){
                Stop();
                SafeRotate('CW', 90);
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
            break;
        case 4:
            //are front sensors hitting nebulite box (& no others?)
            break;
        case 5: //WILL REQUIRE TIMED MOVEMENT
            //are right sensors hitting a wall (& no others?)
            break;
        case 6:
            //is one (or maybe two) front sensors hitting nebulite box?
            break;
        case 7: //WILL REQUIRE TIMED MOVEMENT
            //no sensors should be hitting anything
            break;
        case 8:
            //are one or more left sensors hitting nebulite box?
            ///are front sensors hitting wall?
            break;
        case 9:
            //are front sensors hitting wall?
            break;
        case 10:
            //are one or more front sensors hitting geodinium box?
            break;
        case 11:
            //are front sensors hitting wall?
            break;
        case 12:
            //are front sensors hitting wall?
            //are left sensors hitting wall?
            break;
        case 13:
            //are front sensors hitting geodinium box?
            //are left sensors hitting wall?
            break;
    }
}

//TODO: set up sensor reading code to always assign 9999 to distance if out of range
void SafeRotate(String direction, int angle){
    //if front sensors in range, move backwards until safe distance away
    if(!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)){
        MoveBackwards();
        while(!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)){
            read_multi_sensors(); //how resource intensive is this? will re-reading take too long?
        }
        Stop();
    }
    //if left sensors in range, move right until safe distance away
    if(!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)){
        MoveRight();
        while(!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)){
            read_multi_sensors(); //how resource intensive is this? will re-reading take too long?
        }
        Stop();
    }
    //if right sensors in range, move left until safe distance away
    if(!isSafeDistanceAway(Right_Front) || !isSafeDistanceAway(Right_Back)){
        MoveLeft();
        while(!isSafeDistanceAway(Right_Front) || !isSafeDistanceAway(Right_Back)){
            read_multi_sensors(); //how resource intensive is this? will re-reading take too long?
        }
        Stop();
    }
    //if back sensors in range, move forward until safe distance away
    if(!isSafeDistanceAway(Back_Left) || !isSafeDistanceAway(Back_Right)){
        MoveForwards();
        while(!isSafeDistanceAway(Back_Left) || !isSafeDistanceAway(Back_Right)){
            read_multi_sensors(); //how resource intensive is this? will re-reading take too long?
        }
        Stop();
    }
    if(direction == 'CW'){
        //rotate CW for x degrees
        RotateCW();
        //figure out how to convert time delay to equivalent rotation angle
        Delay(angle)
    }
    else{
        //rotate CCW for x degrees
        RotateCWW();
        //figure out how to convert time delay to equivalent rotation angle
        Delay(angle)
    }
}

void loop(){
    while(objective == setup){
        //do LED stuff
        //when done, set objective to setup
    }
    while(objective == sweepOuterField){
        //state = 1;
        //if state is done executing, move to the next one
        if(state != 3 && LocationHelper(state)){
            state++;
        }
        //end prematurely (Honestly dont think I'll even get this far)
        if(state == 3){
            Stop();
            return;
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
//move south until sweeper hits geodinium container (& corner in bottom left)