//Just Output everything God Damn

bool Debug = true;  //Debug Some Bitches

String OutputSideName(int Side) {
  switch (Side) {
    case Front:
      return "Front ";
      break;
    case Right:
      return "Right ";
      break;
    case Back:
      return "Back ";
      break;
    case Left:
      return "Left ";
      break;
  }
}

String OutputDirectionName(int Direction) {
  switch (Direction) {
    case North:
      return "North ";
      break;
    case East:
      return "East ";
      break;
    case South:
      return "South ";
      break;
    case West:
      return "West ";
      break;
  }
}


void DisplayClosestSideReadings(int ClosestDirection, bool debug) {
  if (debug) {
    Serial.print(OutputSideName(ClosestDirection));  //Outputs Avg dist
    Serial.print("Average Distance = ");
    Serial.print(Side[ClosestDirection].AvgDist);
    Serial.print("      ");
    Serial.print(OutputSideName(ClosestDirection));  //Outputs dif dist
    Serial.print("Distance Diference = ");
    Serial.print(Side[ClosestDirection].SideDif);
    Serial.print("      ");
    Serial.print(OutputSideName(ClosestDirection));  //Outputs left dist
    Serial.print("Left Distance = ");
    Serial.print(Side[ClosestDirection].LDist);
    Serial.print("      ");
    Serial.print(OutputSideName(ClosestDirection));  //Outputs right dist
    Serial.print("Right Distance = ");
    Serial.println(Side[ClosestDirection].RDist);
  }
}