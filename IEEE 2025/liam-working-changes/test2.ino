


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


//I AM ASSUMING SWEEPER IS ALWAYS FRONT, ALL SENSOR DIRECTIONS RELATIVE TO SWEEPER
//        front (sweeper)
        //   @@@@@@@@
        // l |      | r
        // e |      | i
        // f |      | gh
        // t |......| t
        //     back

//figure out the distance away from wall to safely rotate without hitting it
#define safeDistanceAway 100
//figure out the factor which converts angle degrees to delay time while rotating
#define delayScalingFactor 22.388

bool isSafeDistanceAway(int sensor){
  Read_Multi_Sensors();
  Serial.print("Sensor Value ");
  Serial.println(Sensor[sensor].Distance);

    if(Sensor[sensor].Distance < safeDistanceAway){
        return false;
    }
    return true;
}

// I know this should go into its own ino file eventually
bool inPosition = false;
bool LocationHelper(int state){
    switch(state){
        //should be in the pad 0 corner, sweeper facing a wall
        case 1:
            inPosition = false;
            // MoveForward();
            Movement_Adjust("Forward");
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
                SafeRotate("CW", 90);
                return true;
            }
            return false;
            //if no, return false (not in position yet)
            break;
        case 2:
            inPosition = false;
            Movement_Adjust("Forward");
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
            inPosition = false;
            Movement_Adjust("Forward");
            Read_Multi_Sensors();
            if(!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Left_Front) && !isSafeDistanceAway(Left_Back)){
                inPosition = true;
            }
            if(inPosition){
                Stop();
                SafeRotate("CW", 90);
                return true;
            }
            return false;
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
    CheckForWallCollisions();
    
    /*
    //if front sensors in range, move backwards until safe distance away
    if(!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)){
        MoveBackward();
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
        MoveForward();
        while(!isSafeDistanceAway(Back_Left) || !isSafeDistanceAway(Back_Right)){
            read_multi_sensors(); //how resource intensive is this? will re-reading take too long?
        }
        Stop();
    }
    */

    angle = delayScalingFactor * angle;

    if(direction == "CW"){
        //rotate CW for x degrees
        RotateCW();
        //figure out how to convert time delay to equivalent rotation angle
        delay(angle);
        Stop();
    }
    else{
        //rotate CCW for x degrees
        RotateCCW();
        //figure out how to convert time delay to equivalent rotation angle
        delay(angle);
        Stop();
    }
}


 //sweeper hits geodinium container (& corner in bottom left)

 void tempMovementFn(){
    hasMovementStarted = false;
    Serial.println("starting the while loop");
    while(isSafeDistanceAway(Front_Right) && isSafeDistanceAway(Front_Left)){
        Movement_Adjust("Forward");
        Read_Multi_Sensors();
        DisplayReadings(1);
    }
    Serial.println("stopping");
    Stop();
    delay(5000);
    Serial.println("safe rotate");
    SafeRotate("CW", 90);
    // delay(2000);
    // Stop();
    // MoveRight();
    // delay(2000);
    // Stop();
    // MoveLeft();
    // delay(2000);
    // Stop();
    // MoveBackward();
    // delay(2000);
    // Stop();
    // RotateCW();
    // delay(2000);
}