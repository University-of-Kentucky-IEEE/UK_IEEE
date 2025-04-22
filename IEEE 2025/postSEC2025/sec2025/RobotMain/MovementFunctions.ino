#include <Servo.h>
//
//
//    BASIC MOVEMENT FUNCTIONS
//
//

#define MaxPulse 2500
#define MinPulse 500
#define Stall 1500

void RotateCW(float Power) {

  FL.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
  BL.writeMicroseconds(MaxPulse - 1000 * (1 - Power));

  FR.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
  BR.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
}

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

void RotateCCW(float Power) {
  FL.writeMicroseconds(MinPulse + 1000 * (1 - Power));
  BL.writeMicroseconds(MinPulse + 1000 * (1 - Power));

  FR.writeMicroseconds(MinPulse + 1000 * (1 - Power));
  BR.writeMicroseconds(MinPulse + 1000 * (1 - Power));
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

void MoveForward(float Power) {
  FL.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
  BL.writeMicroseconds(MaxPulse - 1000 * (1 - Power));

  FR.writeMicroseconds(MinPulse + 1000 * (1 - Power));
  BR.writeMicroseconds(MinPulse + 1000 * (1 - Power));
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

void MoveRight(float Power) {
  FL.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
  BL.writeMicroseconds(MinPulse + 1000 * (1 - Power));

  FR.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
  BR.writeMicroseconds(MinPulse + 1000 * (1 - Power));
}


void MoveRight() {
  //   FL.writeMicroseconds(MaxPulse);
  //  BL.writeMicroseconds(MaxPulse);

  //   FR.writeMicroseconds(MaxPulse);
  //   BR.writeMicroseconds(MaxPulse);
  FL.writeMicroseconds(MaxPulse);
  BL.writeMicroseconds(MinPulse);

  FR.writeMicroseconds(MaxPulse);
  BR.writeMicroseconds(MinPulse);
}


void MoveLeft(float Power) {

  FL.writeMicroseconds(MinPulse + 1000 * (1 - Power));
  BL.writeMicroseconds(MaxPulse - 1000 * (1 - Power));

  FR.writeMicroseconds(MinPulse + 1000 * (1 - Power));
  BR.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
}

void MoveLeft() {
  // FL.writeMicroseconds(MinPulse);
  // BL.writeMicroseconds(MaxPulse);

  // FR.writeMicroseconds(MinPulse);
  // BR.writeMicroseconds(MaxPulse);
  FL.writeMicroseconds(MinPulse);
  BL.writeMicroseconds(MaxPulse);

  FR.writeMicroseconds(MinPulse);
  BR.writeMicroseconds(MaxPulse);
}

void MoveBackward(float Power) {
  FL.writeMicroseconds(MinPulse + 1000 * (1 - Power));
  BL.writeMicroseconds(MinPulse + 1000 * (1 - Power));

  FR.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
  BR.writeMicroseconds(MaxPulse - 1000 * (1 - Power));
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


void AdjustDistance(int Direction, float Speed) {
  switch (Direction) {
    case Front:
      Serial.println(" Adjust Distance = Forward");
      MoveForward(Speed);
      break;
    case Right:
      Serial.println(" Adjust Distance = Right");
      MoveRight(Speed);
      break;
    case Back:
      Serial.println(" Adjust Distance = Back");
      MoveBackward(Speed);
      break;
    case Left:
      Serial.println(" Adjust Distance = Left");
      MoveLeft(Speed);
      break;
  }
}

//
//
//    MOVEMENT ADJUST
//
//

#define PowerFactor 100
#define Stationary 5

void Movement_Adjust(int Direction, int ReadSide) {  //NEEDS TO BE TESTED
  
  Read_Side(ReadSide);
  float Power = Side[ReadSide].SideDif * 10;
  Serial.println(" ");
  Serial.println(Power);
   Serial.println(" ");

  String SideTilt;

  if (Power > 0) {
    SideTilt = "CCW";
  } else {
    SideTilt = "CW";
  }
  //Movement Mapping
  Power = abs(Power);

  Serial.print("Direction = ");
  Serial.print(Direction);
  Serial.print(" Now Tilting ");
  Serial.println(SideTilt);

  if (Direction == Front) {
    if (SideTilt == "CW") {  //tilting left
      FL.writeMicroseconds(MaxPulse - (Power));
      BL.writeMicroseconds(MaxPulse - (Power));

      FR.writeMicroseconds(MinPulse);
      BR.writeMicroseconds(MinPulse);

    } else if (SideTilt == "CCW") {  // tilting right
      FL.writeMicroseconds(MaxPulse);
      BL.writeMicroseconds(MaxPulse);

      FR.writeMicroseconds(MinPulse +  (Power));
      BR.writeMicroseconds(MinPulse + (Power));

    } else {
      MoveForward();
    }

  } else if (Direction == Back) {

    if (SideTilt == "CCW") {  //tilting left
      FL.writeMicroseconds(MinPulse);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MaxPulse - 1000 * (Power));
      BR.writeMicroseconds(MaxPulse - 1000 * (Power));

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MinPulse);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MaxPulse - 1000 * (Power));
      BR.writeMicroseconds(MaxPulse - 1000 * (Power));

    } else {
      MoveBackward();
    }
  } else if (Direction == Left) {
    if (SideTilt == "CCW") {  //tilting left


      FL.writeMicroseconds(MinPulse);
      BL.writeMicroseconds(MaxPulse - 1000 * Power);

      FR.writeMicroseconds(MinPulse);
      BR.writeMicroseconds(MaxPulse - 1000 * Power);

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MinPulse);
      BL.writeMicroseconds(MaxPulse - 1000 * Power);

      FR.writeMicroseconds(MinPulse);
      BR.writeMicroseconds(MaxPulse - 1000 * Power);
    } else {
      MoveLeft();
    }

  } else if (Direction == Right) {
    if (SideTilt == "CCW") {  //tilting left

      FL.writeMicroseconds(MaxPulse - 1000 * Power);
      BL.writeMicroseconds(MinPulse);

      FR.writeMicroseconds(MaxPulse - 1000 * Power);
      BR.writeMicroseconds(MinPulse);

    } else if (SideTilt == "CW") {  // tilting right
      FL.writeMicroseconds(MaxPulse);
      BL.writeMicroseconds(MinPulse + 1000 * Power);

      FR.writeMicroseconds(MaxPulse);
      BR.writeMicroseconds(MinPulse + 1000 * Power);
    } else {
      MoveRight();
    }

  } else if (Direction == Stationary) {
    if (SideTilt == "CW") {  //tilting left
      FL.writeMicroseconds(MaxPulse * Power);
      BL.writeMicroseconds(MaxPulse * Power);

      FR.writeMicroseconds(MaxPulse * Power);
      BR.writeMicroseconds(MaxPulse * Power);

    } else if (SideTilt == "CCW") {  // tilting right
      FL.writeMicroseconds(MinPulse * Power);
      BL.writeMicroseconds(MinPulse * Power);

      FR.writeMicroseconds(MinPulse * Power);
      BR.writeMicroseconds(MinPulse * Power);

    } else {
      Stop();
    }
  } else {
    Stop();
  }
}


//Hardcode test adjust:Unchecked if working
// void Movement_Adjust(String Direction, String Tilt) {
//   if(Direction == "Forward") {
//     if(Tilt == "cw") {
//       RotateCW();
//       delay(75);
//     }
//     else if(Tilt == "ccw"){
//       RotateCCW();
//       delay(75);
//     }
//     else{
//       Stop();
//     }
//   }

//   //TODO:Need to adjust
//   else if (Direction == "Backward") {
//     if(Tilt == "cw") {
//       RotateCW();
//       delay(75);
//     }
//     else if(Tilt == "ccw"){
//       RotateCCW();
//       delay(75);
//     }
//     else{
//       Stop();
//     }
//   }

//   //TODO:Need to adjust
//   else if(Direction == "Right") {
//     if(Tilt == "cw") {
//       RotateCW();
//       delay(75);
//     }
//     else if(Tilt == "ccw"){
//       RotateCCW();
//       delay(75);
//     }
//     else{
//       Stop();
//     }
//   }

//   //TODO:Need to adjust
//   else if(Direction == "Left") {
//     if(Tilt == "cw") {
//       RotateCW();
//       delay(75);
//     }
//     else if(Tilt == "ccw"){
//       RotateCCW();
//       delay(75);
//     }
//     else{
//       Stop();
//     }

//   }

//   //TODO:Need to adjust
//   else if (Direction == "Stationary") {
//     if(Tilt == "cw") {
//       RotateCW();
//       delay(75);
//     }
//     else if(Tilt == "ccw"){
//       RotateCCW();
//       delay(75);
//     }
//     else{
//       Stop();
//     }
//   }

//   else {
//     Stop();
//   }
// }