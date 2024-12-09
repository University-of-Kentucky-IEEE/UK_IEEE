//
//
// PIXY FUNCTIONS
//
//

int FindDistance(int WantedBlock) {
  int ObjectDistance;
  switch (pixy.ccc.blocks[WantedBlock].m_signature) {
    case 0:
      ObjectDistance = -6.676 * pixy.ccc.blocks[WantedBlock].m_width + 428.63; // Small Package Distance Equation, multiplied by 10 for mm
      break;

    case 1:
      ObjectDistance = -4.552 * pixy.ccc.blocks[WantedBlock].m_width  + 439.41; // Large Package Distance Equation, multiplied by 10 for mm
      break;

    case 2:
      ObjectDistance = -12.718 * pixy.ccc.blocks[WantedBlock].m_width + 452.1; // Fuel Tank Distance Equation, multiplied by 10 for mm
      break;

    case 3:
      ObjectDistance = -4.952 * pixy.ccc.blocks[WantedBlock].m_width + 320.19; // Thruster Distance Equation, multiplied by 10 for mm
      break;

    default:
      ObjectDistance = 100;
      break;
  }
  return ObjectDistance;
}

int PickColoredBlock(int Signature) {  //picks the block with desired color sig out of all the detected blocks

  int blocks = pixy.ccc.getBlocks();  //gets number of blocks
  int WantedBlock = -1;               // block that is of the desired color

  for (int i = 0; i < blocks; i++) {
    if (pixy.ccc.blocks[i].m_signature == Signature) {  // if block is equal to the desired color
      WantedBlock = i;
    }
  }
  return WantedBlock;
}

//probably most of this is useless but it finds the longest vector and gets the angl eof that
float GetAngle(int Signature){
  int WantedBlock = PickColoredBlock(1);
      float Ypos = pixy.ccc.blocks[WantedBlock].m_y;
      float Xpos = pixy.ccc.blocks[WantedBlock].m_x;
      float TargetAngle = -atan((158 - Xpos) / (208 - Ypos)) * (180 / 3.141529);
      Serial.print(" Target angle is ");
      Serial.println(TargetAngle);
      return TargetAngle;
}
void Search(int Signature) {
  float PixyTurnBaseStart = millis();  //sets Time start so we dont repeat the search forever
  bool FoundObject = false;

  int SearchDegree[2];  //[Min, Max] Seach Turn degree
  switch (Signature) {
    case 0:  //small packages
      SearchDegree[0] = 90;
      SearchDegree[1] = 130;
      break;

    case 1:  //large packages
      SearchDegree[0] = 170;
      SearchDegree[1] = MAX_BASE_ANGLE;
      break;

    case 2:  //fuel Tanks
      SearchDegree[0] = 90;
      SearchDegree[1] = 130;
      break;

    case 3:  //thrusters
      SearchDegree[0] = 170;
      SearchDegree[1] = MAX_BASE_ANGLE;
      break;

    default:
      SearchDegree[0] = 90;
      SearchDegree[1] = 130;
      break;
  }
  bool Direction = true;  // true = cw, false = ccw
  GetBaseAngle();
  do {

    if (Direction) {  //cw
      BaseServo.writeMicroseconds(MaxPulse);
    } else {  //ccw
      BaseServo.writeMicroseconds(MinPulse);
    }
    GetBaseAngle();
    if(CurrentBaseAngle >= SearchDegree[1]){
      Direction = false;
    } 
    if(CurrentBaseAngle <= SearchDegree[0]){
      Direction = true;
    } 

  WantedObject = PickColoredBlock(Signature);
  if (pixy.ccc.blocks[WantedObject].m_x >= PixyImageCenter + PixelOffset) { //block is to the right of image center + offset
    Direction = true;
  }
  if (pixy.ccc.blocks[WantedObject].m_x <= PixyImageCenter - PixelOffset) { //block is to the left of image center - offset
    Direction = false;
  } 
  if ((pixy.ccc.blocks[WantedObject].m_x >= PixyImageCenter - PixelOffset) && (pixy.ccc.blocks[WantedObject].m_x <= PixyImageCenter + PixelOffset)) {     //within center
    BaseServo.writeMicroseconds(Stall);
    FoundObject = true; 
  }


  } while (((millis() - PixyTurnBaseStart) <= 5000) && (!FoundObject));  //while seach has not gone on for more than 5 seconds and object has not been found
  BaseServo.writeMicroseconds(Stall);                                    //Stops Rotating Base

  if (FoundObject){ //pickup object if one is found
    PickupObject(Signature);
  }
} 