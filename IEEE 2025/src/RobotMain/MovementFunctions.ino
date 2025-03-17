#pragma once
#include "Global_Int.h"
//
//
//    BASIC MOVEMENT FUNCTIONS
//
//

void RotateCW() {
  // FL.writeMicroseconds(MaxPulse);
  // BL.writeMicroseconds(MaxPulse);

  // FR.writeMicroseconds(MaxPulse);
  // BR.writeMicroseconds(MaxPulse);
    FL.writeMicroseconds(MaxPulse);
BL.writeMicroseconds(MaxPulse);

FR.writeMicroseconds(MaxPulse);
BR.writeMicroseconds(MaxPulse);
}

void RotateCCW() {
  // FL.writeMicroseconds(MinPulse);
  // BL.writeMicroseconds(MinPulse);

  // FR.writeMicroseconds(MinPulse);
  // BR.writeMicroseconds(MinPulse);
    FL.writeMicroseconds(MinPulse);
  BL.writeMicroseconds(MinPulse);
  
  FR.writeMicroseconds(MinPulse);
  BR.writeMicroseconds(MinPulse);
}

void MoveForward() {
  // FL.writeMicroseconds(MinPulse);
  // BL.writeMicroseconds(MaxPulse);

  // FR.writeMicroseconds(MaxPulse);
  // BR.writeMicroseconds(MinPulse);
  FL.writeMicroseconds(MaxPulse);
BL.writeMicroseconds(MaxPulse);

FR.writeMicroseconds(MinPulse);
BR.writeMicroseconds(MinPulse);
}

void MoveRight() {
//   FL.writeMicroseconds(MaxPulse);
//  BL.writeMicroseconds(MaxPulse);

//   FR.writeMicroseconds(MaxPulse);
//   BR.writeMicroseconds(MaxPulse);
FL.writeMicroseconds(MinPulse);
BL.writeMicroseconds(MaxPulse);

FR.writeMicroseconds(MaxPulse);
BR.writeMicroseconds(MinPulse);
}

void MoveLeft() {
  // FL.writeMicroseconds(MinPulse);
  // BL.writeMicroseconds(MaxPulse);

  // FR.writeMicroseconds(MinPulse);
  // BR.writeMicroseconds(MaxPulse);
  FL.writeMicroseconds(MaxPulse);
  BL.writeMicroseconds(MinPulse);

  FR.writeMicroseconds(MinPulse);
  BR.writeMicroseconds(MaxPulse);
}

void MoveBackward() {
    FL.writeMicroseconds(MinPulse);
BL.writeMicroseconds(MinPulse);

FR.writeMicroseconds(MaxPulse);
BR.writeMicroseconds(MaxPulse);
  // FL.writeMicroseconds(MaxPulse);
  // BL.writeMicroseconds(MinPulse);

  // FR.writeMicroseconds(MinPulse);
  // BR.writeMicroseconds(MaxPulse);
  // FL.writeMicroseconds(MinPulse);
  // BL.writeMicroseconds(MinPulse);
  
  // FR.writeMicroseconds(MinPulse);
  // BR.writeMicroseconds(MinPulse);
}

void Stop() {
  FL.writeMicroseconds(Stall);
  BL.writeMicroseconds(Stall);

  FR.writeMicroseconds(Stall);
  BR.writeMicroseconds(Stall);
}

//
//
//    MOVEMENT ADJUST
//
//
void Movement_Adjust(String Direction) {  //NEEDS TO BE TESTED

  int MappedSpeed[4];  // 0 min to max, 1 max to min pulse
  //Movement Mapping
  MappedSpeed[0] = map(SideDif, 0, -100, Stall, MinPulse);
  MappedSpeed[1] = map(SideDif, 0, 100, Stall, MaxPulse);

  //Stationary Mapping
  MappedSpeed[2] = map(SideDif, 0, 100, Stall, MaxPulse);
  MappedSpeed[3] = map(SideDif, 0, 100, Stall, MinPulse);
  Serial.println(MappedSpeed[2]);
  Serial.println(MappedSpeed[3]);

  Serial.print("Direction = ");
  Serial.print(Direction);
  Serial.print(" Now Tilting ");
  Serial.println(SideTilt);

  if (Direction == "Forward") {
    if (SideTilt == "CWW") {  //tilting left
      FL.writeMicroseconds(MappedSpeed[0]);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MaxPulse);
      BR.writeMicroseconds(MappedSpeed[0]);

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MappedSpeed[0]);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MaxPulse);
      BR.writeMicroseconds(MappedSpeed[0]);

    } else {
      MoveForward();
    }

  } else if (Direction == "Backward") {

    if (SideTilt == "CWW") {  //tilting left
      FL.writeMicroseconds(MappedSpeed[1]);
      BL.writeMicroseconds(MappedSpeed[1]);

      FR.writeMicroseconds(MinPulse);
      BR.writeMicroseconds(MinPulse);

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MaxPulse);
      BL.writeMicroseconds(MaxPulse);

      FR.writeMicroseconds(MappedSpeed[0]);
      BR.writeMicroseconds(MappedSpeed[0]);

    } else {
      MoveBackward();
    }
  } else if (Direction == "Left") {
    if (SideTilt == "CCW") {  //tilting left
                              /*
      FL.writeMicroseconds(MaxPulse);
  BL.writeMicroseconds(MinPulse);

  FR.writeMicroseconds(MaxPulse);
  BR.writeMicroseconds(MinPulse);
*/
      FL.writeMicroseconds(MappedSpeed[0]);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MappedSpeed[0]);
      BR.writeMicroseconds(MinPulse);

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MappedSpeed[0]);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MappedSpeed[0]);
      BR.writeMicroseconds(MinPulse);
    } else {
      MoveLeft();
    }

  } else if (Direction == "Right") {
    if (SideTilt == "CWW") {  //tilting left

      FL.writeMicroseconds(MappedSpeed[0]);
      BL.writeMicroseconds(MaxPulse);

      FR.writeMicroseconds(MappedSpeed[1]);
      BR.writeMicroseconds(MaxPulse);

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MappedSpeed[0]);
      BL.writeMicroseconds(MaxPulse);

      FR.writeMicroseconds(MappedSpeed[1]);
      BR.writeMicroseconds(MaxPulse);
      /*
      FL.writeMicroseconds(MinPulse);
      BL.writeMicroseconds(MappedSpeed[1]);

      FR.writeMicroseconds(MaxPulse);
      BR.writeMicroseconds(MappedSpeed[0]);
      */
    } else {
      MoveRight();
    }

  } else if (Direction == "Stationary") {
    if (SideTilt == "CW") {  //tilting left
      FL.writeMicroseconds(MappedSpeed[2]);
      BL.writeMicroseconds(MappedSpeed[2]);

      FR.writeMicroseconds(MappedSpeed[2]);
      BR.writeMicroseconds(MappedSpeed[2]);

    } else if (SideTilt == "CCW") {  // tilting right
      FL.writeMicroseconds(MappedSpeed[2]);
      BL.writeMicroseconds(MappedSpeed[2]);

      FR.writeMicroseconds(MappedSpeed[2]);
      BR.writeMicroseconds(MappedSpeed[2]);

    } else {
      Stop();
    }
  } else {
    Stop();
  }
}