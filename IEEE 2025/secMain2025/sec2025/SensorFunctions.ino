#pragma once
#include "Global_Int.h"
//functions work :D

void setID() {
  // all reset
  DisableSensors();
  delay(10);
  // all unreset
  EnableSensors();

  delay(10);

  // activating LOX1 and resetting LOX2
  DisableSensors();
  delay(10);
  digitalWrite(SHT_LOX1, HIGH);
  delay(10);

  // initing LOX1
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
  }
  delay(10);

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  if (!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
  }
  delay(10);

  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  //initing LOX4
  if (!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot fourth VL53L0X"));
  }
  delay(10);

  // activating LOX5
  digitalWrite(SHT_LOX5, HIGH);
  delay(10);

  //initing LOX5
  if (!lox5.begin(LOX5_ADDRESS)) {
    Serial.println(F("Failed to boot fith VL53L0X"));
  }
  delay(10);

  // activating LOX6
  digitalWrite(SHT_LOX6, HIGH);
  delay(10);

  //initing LOX6
  if (!lox6.begin(LOX6_ADDRESS)) {
    Serial.println(F("Failed to boot sixth VL53L0X"));
  }
  delay(10);

  // activating LOX7
  digitalWrite(SHT_LOX7, HIGH);
  delay(10);

  //initing LOX7
  if (!lox7.begin(LOX7_ADDRESS)) {
    Serial.println(F("Failed to boot seventh VL53L0X"));
  }
  delay(10);

  // activating LOX8
  digitalWrite(SHT_LOX8, HIGH);
  delay(10);

  //initing LOX8
  if (!lox8.begin(LOX8_ADDRESS)) {
    Serial.println(F("Failed to boot eigth VL53L0X"));
  }

  // activating LOX8
  digitalWrite(SHT_LOX9, HIGH);
  delay(10);

  //initing LOX8
  if (!lox9.begin(LOX9_ADDRESS)) {
    Serial.println(F("Failed to boot ninth VL53L0X"));
  }

  // activating LOX8
  digitalWrite(SHT_LOX10, HIGH);
  delay(10);

  //initing LOX8
  if (!lox10.begin(LOX10_ADDRESS)) {
    Serial.println(F("Failed to boot tenth VL53L0X"));
  }
}

void read_multi_sensors() {

  lox1.rangingTest(&measure1, false);    // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false);    // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false);    // pass in 'true' to get debug data printout!
  lox4.rangingTest(&measure4, false);    // pass in 'true' to get debug data printout!
  lox5.rangingTest(&measure5, false);    // pass in 'true' to get debug data printout!
  lox6.rangingTest(&measure6, false);    // pass in 'true' to get debug data printout!
  lox7.rangingTest(&measure7, false);    // pass in 'true' to get debug data printout!
  lox8.rangingTest(&measure8, false);    // pass in 'true' to get debug data printout!
  lox9.rangingTest(&measure9, false);    // pass in 'true' to get debug data printout!
  lox10.rangingTest(&measure10, false);  // pass in 'true' to get debug data printout!


  // print sensor one reading

  if (measure1.RangeStatus != 4) {  // if not out of range
    Sensor[Front_Right].Distance = measure1.RangeMilliMeter;
  }

  // print sensor two reading
  if (measure2.RangeStatus != 4) {
    Sensor[Front_Left].Distance = measure2.RangeMilliMeter * 1.2;
  }
  // print sensor three reading
  if (measure3.RangeStatus != 4) {
    Sensor[Left_Front].Distance = measure3.RangeMilliMeter;
  }
  // print sensor four reading
  if (measure4.RangeStatus != 4) {
    Sensor[Left_Back].Distance = measure4.RangeMilliMeter;
  }
  Serial.print(F(" "));
  // print sensor five reading
  if (measure5.RangeStatus != 4) {
    Sensor[Back_Left].Distance = measure5.RangeMilliMeter;
  }
  // print sensor six reading
  if (measure6.RangeStatus != 4) {
    Sensor[Back_Right].Distance = measure6.RangeMilliMeter;
  }
  // print sensor seven reading
  if (measure7.RangeStatus != 4) {
    Sensor[Right_Front].Distance = measure7.RangeMilliMeter;
  }
  // print sensor eight reading
  if (measure8.RangeStatus != 4) {
    Sensor[Right_Back].Distance = measure8.RangeMilliMeter;
  }
  // print sensor eight reading
  if (measure9.RangeStatus != 4) {
    Sensor[Under_Front].Distance = measure9.RangeMilliMeter;
  }
  // print sensor eight reading
  if (measure10.RangeStatus != 4) {
    Sensor[Under_Back].Distance = measure10.RangeMilliMeter;
  }
}

void read_single_sensor(int SensorPointer) {
  switch (SensorPointer) {
    case 0:
      lox1.rangingTest(&measure1, false);  // pass in 'true' to get debug data printout!
      if (measure1.RangeStatus != 4) {     // if not out of range
        Sensor[Front_Right].Distance = measure1.RangeMilliMeter;
      }
      break;

    case 1:
      lox2.rangingTest(&measure2, false);  // pass in 'true' to get debug data printout!
      if (measure2.RangeStatus != 4) {     // if not out of range
        Sensor[Front_Left].Distance = measure2.RangeMilliMeter - 12;
      }
      break;

    case 2:
      lox3.rangingTest(&measure3, false);  // pass in 'true' to get debug data printout!
      if (measure3.RangeStatus != 4) {     // if not out of range
        Sensor[Left_Front].Distance = measure3.RangeMilliMeter;
      }
      break;

    case 3:
      lox4.rangingTest(&measure4, false);  // pass in 'true' to get debug data printout!
      if (measure4.RangeStatus != 4) {     // if not out of range
        Sensor[Left_Back].Distance = measure4.RangeMilliMeter;
      } else {
        Sensor[Left_Back].Distance = 9999;
      }
      break;

    case 4:
      lox5.rangingTest(&measure5, false);  // pass in 'true' to get debug data printout!
      if (measure5.RangeStatus != 4) {     // if not out of range
        Sensor[Right_Front].Distance = measure5.RangeMilliMeter;
      }
      break;

    case 5:
      lox6.rangingTest(&measure6, false);  // pass in 'true' to get debug data printout!
      if (measure6.RangeStatus != 4) {     // if not out of range
        Sensor[Right_Back].Distance = measure6.RangeMilliMeter;
      }
      break;

    case 6:
      lox7.rangingTest(&measure7, false);  // pass in 'true' to get debug data printout!
      if (measure7.RangeStatus != 4) {     // if not out of range
        Sensor[Back_Right].Distance = measure7.RangeMilliMeter;
      } else {
        Sensor[Back_Right].Distance = 9999;
      }
      break;

    case 7:
      lox8.rangingTest(&measure8, false);  // pass in 'true' to get debug data printout!
      if (measure8.RangeStatus != 4) {     // if not out of range
        Sensor[Back_Left].Distance = measure8.RangeMilliMeter;
      }
      break;

    case 8:
      lox9.rangingTest(&measure9, false);  // pass in 'true' to get debug data printout!
      if (measure9.RangeStatus != 4) {     // if not out of range
        Sensor[Under_Front].Distance = measure9.RangeMilliMeter;
      }
      break;

    case 9:
      lox10.rangingTest(&measure10, false);  // pass in 'true' to get debug data printout!
      if (measure10.RangeStatus != 4) {      // if not out of range
        Sensor[Under_Back].Distance = measure10.RangeMilliMeter;
      }
      break;
  }
}
void Read_Multi_Sensors() {

  read_single_sensor(Front_Left);
  read_single_sensor(Front_Right);
  read_single_sensor(Right_Front);
  read_single_sensor(Right_Back);
  read_single_sensor(Left_Front);
  read_single_sensor(Left_Back);
  read_single_sensor(Back_Right);
  read_single_sensor(Back_Left);
  read_single_sensor(Under_Front);
  read_single_sensor(Under_Back);
}

void SetupSensors() {
  EnableSensors();
  Serial.println(F("Shutdown pins inited..."));
  DisableSensors();
  Serial.println(F("All in reset mode...(pins are low)"));
  for (int i = 0; i < TotalSensors; i++) {
    String Number[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    Sensor[i].LOX_ADDRESS = 0x30 + i;
    Sensor[i].Xshut = 22 + i;
    Sensor[i].Name = "Sensor " + Number[i];
  }
  setID();
}

void DisableSensors() {
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  digitalWrite(SHT_LOX5, LOW);
  digitalWrite(SHT_LOX6, LOW);
  digitalWrite(SHT_LOX7, LOW);
  digitalWrite(SHT_LOX8, LOW);
  digitalWrite(SHT_LOX9, LOW);
  digitalWrite(SHT_LOX10, LOW);
}

void EnableSensors() {
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);
  pinMode(SHT_LOX5, OUTPUT);
  pinMode(SHT_LOX6, OUTPUT);
  pinMode(SHT_LOX7, OUTPUT);
  pinMode(SHT_LOX8, OUTPUT);
  pinMode(SHT_LOX9, OUTPUT);
  pinMode(SHT_LOX10, OUTPUT);
}

void FindTilt(float Distance1, float Distance2) {  //Gets tilt from sensor readings

  SideDif = Distance1 - Distance2;

  if (SideDif > 0) {  //Left Higher
    SideTilt = "CW";
  }
  if (SideDif < 0) {  //Right Higher
    SideTilt = "CCW";
  }
  if (SideDif == 0) {  //no tilt
    SideTilt = "Even";
  }
}


//NEEDS TESTING
bool DetectLocation(int Location) {
  bool InPosition = false;
  switch (Location) {
    case Package_Delivery_Site:  //Package_Delivery_Site
      read_single_sensor(Front_Right);
      read_single_sensor(Left_Back);
      read_single_sensor(Back_Right);
      read_single_sensor(Right_Front);
      read_single_sensor(Back_Left);
      while (Sensor[Right_Front].Distance <= 90){
        read_single_sensor(Right_Front);
        MoveLeft();
      } 
      while (Sensor[Right_Front].Distance >= 150){
        read_single_sensor(Right_Front);
        MoveRight();
      }


      if ((Sensor[Front_Right].Distance <= 210) && (Sensor[Left_Back].Distance >= 500) && ((Sensor[Back_Right].Distance <= 600) && (Sensor[Back_Right].Distance >= 150)) && ((Sensor[Back_Left].Distance <= 600) && (Sensor[Back_Left].Distance >= 150))) {  //if front sensors are close to the front wall and left sensors are further than usual we have hit the first wall
        read_single_sensor(Right_Front);
        Serial.println("Close to First Corner");

        if (Sensor[Right_Front].Distance >= 100) {  //if we are close to first corner but too far from right side wall move closer to the wall
          Serial.println("Robot is near first corner but far from right wall!!!");
          while (Sensor[Right_Front].Distance >= 150) {
            read_single_sensor(Right_Front);
            // read_single_sensor(Right_Back);
            DisplayReadings(1);
            MoveRight();
          }
        }


        Serial.println("Robot is now in posiiton to Deliver Packages!");
        Stop();  //now in position
        InPosition = true;
      }
      //}
      break;

    case Fuel_Tank_Pickup:  //Fuel_Tank_Pickup
      read_single_sensor(Front_Right);
      read_single_sensor(Left_Back);
      Serial.print("Front Right Distance ");
      Serial.println(Sensor[Front_Right].Distance);
      while (Sensor[Front_Right].Distance <= 190) {
        read_single_sensor(Front_Right);
        Serial.println("Too close to wall");
        MoveBackward();
      }
      while (Sensor[Front_Right].Distance >= 250) {
        read_single_sensor(Front_Right);
        Serial.println("Too far from wall");
        MoveForward();
      }
      if (Sensor[Left_Back].Distance <= 175) {
        if ((Sensor[Front_Right].Distance < 250) && ((Sensor[Front_Right].Distance >= 190))) {
          Serial.println("Robot is now in posiiton to pick up fuel tanks!");
          Stop();  //now in position
          InPosition = true;
        }
      }
      break;

    case Trench_Start:  //Trench_Start
      read_single_sensor(Under_Front);
      if (Sensor[Under_Front].Distance >= 130) {  //if front under sensor is detecting a distance further away than usual
        Stop();
        InPosition = true;
      }

      break;

    case Tench_Middle:  //Tench_Middle
      read_single_sensor(Under_Back);
      if (Sensor[Under_Back].Distance >= 130) {  //if front under sensor is detecting a distance further away than usual
        Stop();
        InPosition = true;
      }

      break;

    case Tench_End:  //Tench_End
      read_single_sensor(Under_Back);
      if (Sensor[Under_Back].Distance >= 80) {  //if front under sensor is detecting a distance further away than usual
        Stop();
        InPosition = true;
      }

      break;

    case Rocket_Assembly:  //Rocket_Assembly
      read_single_sensor(Back_Right);
      read_single_sensor(Right_Front);
      read_single_sensor(Front_Right);

      if (Sensor[Back_Right].Distance <= 150 && Sensor[Front_Right].Distance <= 500) {
        if (Sensor[Right_Front].Distance <= 120) {  //In position
          Stop();
          InPosition = true;
        } else {  //close to front wall but too far from Left wall (Robot is facing backwards)
          while (Sensor[Right_Front].Distance >= 120) {
            read_single_sensor(Right_Front);
            MoveRight();
          }
          Stop();
          InPosition = true;
        }
      } else if (Sensor[Right_Front].Distance <= 90) {
        MoveLeft();
      } else if (Sensor[Right_Front].Distance >= 150) {
        MoveRight();
      } else if (Sensor[Back_Right].Distance <= 100) {
        MoveForward();
      }


      break;

    case Button:  //Button
      read_single_sensor(Front_Left);
      read_single_sensor(Left_Back);
      if (Sensor[Front_Right].Distance <= 200) {
      }


      break;

    default:
      InPosition = false;
      break;
  }
  return InPosition;
}