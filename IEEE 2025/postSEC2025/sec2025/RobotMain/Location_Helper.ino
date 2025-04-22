// I know this should go into its own ino file eventually
bool inPosition = false;
bool hasCaseStarted = false;

// bool LocationHelper(int state) {
//   switch (state) {
//     //should be in the pad 0 corner, sweeper facing a wall
//     case 1:
//       hasCaseStarted = true;
//       inPosition = false;
//       // MoveForward();
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       //are front sensors hitting wall?
//       //are left sensors hitting wall?
//       if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
//         if (!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
//           inPosition = true;
//         }
//       }
//       //if yes, do the safe rotation adjustment and rotate
//       if (inPosition) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;

//       //if no, return false (not in position yet)
//       break;
//     case 2:
//       hasCaseStarted = true;
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       //are front sensors hitting wall?
//       //are left sensors hitting wall?
//       if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
//         if (!isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
//           inPosition = true;
//         }
//       }
//       //if yes, do the safe rotation adjustment and rotate
//       if (inPosition) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;
//       //if no, return false (not in position yet)
//       break;
//     case 3:
//       //are some of front sensors hitting wall?
//       //are left sensors hitting wall?
//       //if yes, do the safe rotation adjustment and rotate
//       //if no, adjust position until OK to do so
//       hasCaseStarted = true;
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Left_Front) || !isSafeDistanceAway(Left_Back)) {
//         inPosition = true;
//       }
//       if (inPosition) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;
//       break;
//     case 4:
//       hasCaseStarted = true;
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
//         inPosition = true;
//       }
//       //facing the south wall
//       if (inPosition) {
//         Stop();
//         SafeRotate("CCW", 90);
//         return true;
//       }
//       return false;
//       break;
//     case 5:  //WILL REQUIRE TIMED MOVEMENT
//       //are right sensors hitting a wall (& no others?)
//       hasCaseStarted = true;
//       Movement_Adjust("Forward");
//       delay(500);
//       Stop();
//       SafeRotate("CCW", 90);
//       return true;
//       break;
//     case 6:
//       //is one (or maybe two) front sensors hitting nebulite box?
//       inPosition = false;
//       hasCaseStarted = true;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Left)) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;

//       break;
//     case 7:  //WILL REQUIRE TIMED MOVEMENT
//       //no sensors should be hitting anything
//       inPosition = false;
//       hasCaseStarted = true;
//       Movement_Adjust("Forward");
//       delay(500);
//       Stop();
//       SafeRotate("CCW", 90);
//       return true;
//       break;
//     case 8:
//       //are one or more left sensors hitting nebulite box?
//       ///are front sensors hitting wall?
//       inPosition = false;
//       hasCaseStarted = true;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Left_Front)) {
//         inPosition = true;
//       }
//       //turn around to face the south wall ( not there yet)
//       if (inPosition) {
//         Stop();
//         SafeRotate("CCW", 180);
//         return true;
//       }
//       return false;
//       break;
//     case 9:
//       //are front sensors hitting wall?
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Left) || !isSafeDistanceAway(Front_Right)) {
//         inPosition = true;
//       }
//       if (inPosition) {
//         Stop();
//         SafeRotate("CCW", 90);
//         return true;
//       }
//       return false;
//       break;
//     case 10:
//       //are one or more front sensors hitting geodinium box?
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Right)) {
//         inPosition = true;
//       }
//       if (inPosition) {
//         Stop();
//         SafeRotate("CCW", 90);
//         return true;
//       }
//       return false;
//       break;
//     case 11:
//       //are front sensors hitting wall?
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Front_Left)) {
//         inPosition = true;
//       }
//       if (inPosition) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;
//       break;
//     case 12:
//       //are front sensors hitting wall?
//       //are left sensors hitting wall?
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Front_Left)) {
//         inPosition = true;
//       }
//       if (inPosition) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;
//       break;
//     case 13:
//       //are front sensors hitting geodinium box?
//       //are left sensors hitting wall?
//       inPosition = false;
//       Movement_Adjust("Forward");
//       Read_Multi_Sensors();
//       if (!isSafeDistanceAway(Front_Right) || !isSafeDistanceAway(Front_Left)) {
//         inPosition = true;
//       }
//       if (inPosition) {
//         Stop();
//         SafeRotate("CW", 90);
//         return true;
//       }
//       return false;
//       break;
//   }
// }

/*
void loop() {

  while (objective == setupTasks) {
    SenseLight(A0);
    //do LED stuff
    //when done, set objective to setup
  }
  while (objective == sweepOuterField) {
    CheckForMagnet();
    // if state is done executing, move to the next one
    if(LocationHelper(state)){
        Serial.print("State ");
        Serial.println(state);
        Serial.print(" Cleared Moving to State ");
        Serial.println(state + 1);
        state++;
    }
    if (state == 12){
      objective = pickUpBoxes;
    }

  }
  while (objective == pickUpBoxes) {

  }
  while (objective == dropOffBlocks) {
  }
  while (objective == sweepCave) {
  }
  while (objective == dropOffBlocksFromCave) {
  }
  while (objective == beacon) {
  }
}
*/

int DropOffLocation = 0;  //Drop Off Area
float TimeToMove = 0.0;
//Liam's Location Helper Updates
bool LocationHelper(int state) {
  Serial.print("Location Helper State = ");
  Serial.println(state);
  switch (state) {
    //should be in the pad 0 corner, sweeper facing Left wall
    case 1:  //Move to bottom left Corner
      hasCaseStarted = true;
      inPosition = false;
      // MoveForward();
      Serial.print("Location Helper State Starting ");
      Serial.println(state);
      Serial.println(" ");
      Serial.println(state);
      MoveForward(.5);
      LineMove(Left, 75, 0.5);
      Read_Side(Front);
      Read_Side(Left);
      //are front sensors hitting wall?
      //are left sensors hitting wall?
      if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }

      //if yes, do the safe rotation adjustment and rotate
      if (inPosition) {
        Stop();
        CheckForTurn(CW);
        RamWall(Back);
        return true;
      }
      return false;

      //if no, return false (not in position yet)
      break;

    case 2:  //Move From Bottom Left corner to top left corner
      hasCaseStarted = true;
      inPosition = false;
      MoveForward(.5);

      LineMove(Left, 75, 0.5);
      Read_Side(Front);
      Read_Side(Left);
      //are front sensors hitting wall?
      //are left sensors hitting wall?
      if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }

      //if yes, do the safe rotation adjustment and rotate
      if (inPosition) {
        Stop();
        CheckForTurn(CW);  //Rotate 90 degrees
        RamWall(Left);     //Ram Backwards
        return true;
      }
      return false;
      //if no, return false (not in position yet)
      break;

    case 3:  //Move to First Shipping container
      //are some of front sensors hitting wall?
      //are left sensors hitting wall?
      //if yes, do the safe rotation adjustment and rotate
      //if no, adjust position until OK to do so
      hasCaseStarted = true;
      inPosition = false;

      MoveForward(.2);
      LineMove(Left, 75, 0.5);
      Read_Side(Front);
      Read_Side(Left);

      if (!isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }

      if (inPosition) {
        Stop();
        CheckForTurn(CW);  //Rotate 90 degrees
        RamWall(Back);     //Ram Backwards
        return true;
      }
      return false;
      break;

    case 4:
    inPosition = false; 
    MoveForward(.5);
    Read_Side(Back);
    if (Side[Back].AvgDist >= 200){ // Test the distance is correct
      inPosition = true; 
    } 
    if (inPosition) {
      Stop();
      return true;
    }
    return false;
    break;

    case 5: 
    inPosition = false; 
    GrabShippingContainer(false)
    MoveLeft(.5);
    Read_Side(Back);
    Read_Side(Right);
    if (Side[Right].AvgDist >= 250){ // Test the distance is correct (could be 350)
      inPosition = true;
    }

    if (inPosition) {
      Stop();
      GrabShippingContainer(true);
      MoveForward(.5);
      delay(250);
      Stop();
      return true;
    }
    
    return false; 
    break;

    
    case 6:
      hasCaseStarted = true;
      inPosition = false;
      MoveForward(.5);
      LineMove(Right, 290, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Right);

      if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }
      //facing the south wall
      if (inPosition) {
        Stop();
        CheckForTurn(CCW);      //Rotate 90 degrees
        RamWall(Right);         //Ram Right
        TimeToMove = millis();  // Sets time to move
        return true;
      }
      return false;
      break;

    case 7:  //WILL REQUIRE TIMED MOVEMENT
      //are right sensors hitting a wall (& no others?)
      hasCaseStarted = true;
      MoveForward(.5);
      LineMove(Right, 300, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Right);

      if ((millis() - TimeToMove) > 1000) {
        Stop();
        CheckForTurn(CCW);  //Rotate 90 degrees
        RamWall(Back);      //Ram Backwards
        return true;
      } else {
        return false;
      }

      break;

    case 8:  //Move Away from storage container
      //is one (or maybe two) front sensors hitting nebulite box? Back one is
      inPosition = false;
      hasCaseStarted = true;
      MoveForward(.5);
      Read_Side(Left);
      if (isSafeDistanceAway(Left_Back)) {  // once Left Back isnt close to storage container NEEDS TESTING!!
        Stop();
        CheckForTurn(CW);  //Rotate 90 degrees
        return true;
      }
      return false;
      break;

    case 9:  //Move To South Wall

      inPosition = false;
      hasCaseStarted = true;
      MoveForward(.5);
      LineMove(Right, 500, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Right);

      if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }

      //facing the south wall
      if (inPosition) {
        Stop();
        CheckForTurn(CCW);      //Rotate 90 degrees
        RamWall(Right);         //Ram Right
        TimeToMove = millis();  // Sets time to move
        return true;
      }
      return false;
      break;

    case 10:
      //are one or more Front sensors hitting nebulite box?
      ///are front sensors hitting wall?
      inPosition = false;
      hasCaseStarted = true;
      MoveForward(.5);
      LineMove(Right, 75, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Right);

      if (isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {  // Front Left should be safe distance away while Front Right will be very close to storage container
        inPosition = true;
      }

      //turn around to face the south wall ( not there yet)
      if (inPosition) {
        Stop();
        CheckForTurn(CCW);  //Rotate 90 degrees
        RamWall(Back);      //Ram Back
        return true;
      }
      return false;
      break;

    case 11:  //Move to top Wall
      //are front sensors hitting wall?
      inPosition = false;
      MoveForward(.5);
      LineMove(Right, 150, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Right);

      if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        CheckForTurn(CW);  //Rotate 90 degrees
        RamWall(Left);     //Ram Left
        return true;
      }
      return false;
      break;


    case 12:  // Move to Top Right Corner

      inPosition = false;
      MoveForward(.5);
      LineMove(Left, 75, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Left);
      if (!isSafeDistanceAway(Front_Left) && !isSafeDistanceAway(Front_Right)) {
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        CheckForTurn(CW);  //Rotate 90 degrees
        RamWall(Back);     //Ram Back
        RamWall(Left);     //Ram Left
        return true;
      }
      return false;
      break;


    case 13:  //Move to Bottom Right Corner

      inPosition = false;
      MoveForward(.5);
      LineMove(Left, 75, 0.5);  //TEST DISTANCE!!!!
      Read_Side(Front);
      Read_Side(Left);
      if (!isSafeDistanceAway(Front_Right) && !isSafeDistanceAway(Front_Left)) {  //Test &&
        inPosition = true;
      }
      if (inPosition) {
        Stop();
        CheckForTurn(CW);  //Rotate 90 degrees
        //Turn to have back of robot face Storage Container
        RamWall(Back);     //Ram Back
        CheckForTurn(CW);  //Rotate 90 degrees
        RamWall(Left);
        return true;
      }
      return false;
      break;


    case 14:
      inPosition = false;
      
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
    case 15:
      //are front sensors hitting geodinium box?
      //are left sensors hitting wall?
      inPosition = false;
      
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