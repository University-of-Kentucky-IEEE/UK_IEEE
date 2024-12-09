#include <Servo.h>
#include <Pixy2.h>
#include "Adafruit_VL53L0X.h"
#include "Global_Int.h"

Pixy2 pixy;



void setup() {
  Serial.begin(115200);
  BaseServo.attach(11);


  // wait until serial port opens for native USB devices
  while (!Serial) { delay(1); }
  SetupSensors();


  Serial.println(F("Starting robot..."));
  SetupServos();
  pixy.init();
  pixy.setLamp(0, 0);
}

void loop() {


MoveForward();
/*
int WantedBlock = PickColoredBlock(1);
int Distance = FindDistance(WantedBlock);
Serial.println(Distance);
int Angle = GetAngle(0);
*/

 //Read_Multi_Sensors();
  //read_single_sensor(Back_Left);
 //DisplayReadings(1);

 // Stop();


  /*
delay(1000);
TurnServo(FrontCaster, FrontCaster_ID, 180 , 1000);
delay(1000);
TurnServo(FrontCaster, FrontCaster_ID, 270 , 1000);
delay(1000);
*/
 //Level = Locate_Package_Delivery_Site;
 //Level = Locate_Thrusters;

  /*

MoveForward();
delay(5000);
Stop();
delay(50000);

*/




  while (Level == LED_Startup) {  //LED STARTUP SEQUENCE
    curAvg = LightAverage(photoRpin);
    Serial.print("cur avg need to beat: ");
    if (curAvg >= (1.2 * prevAvg)) {  // if current average is greater than 1.2x prevAvg
      Level = Find_Large_Packages;
      break;
    }

    prevAvg = curAvg;  // current becomes previous to compare with next current.
  }

  while (Level == Find_Large_Packages) {  //Finding Large Packages
  }

  while (Level == Find_Small_Packages) {
  }

  while (Level == Locate_Package_Delivery_Site) {

    DisplayReadings(1);

    MoveForward();
    if (!InPlace1) {
      InPlace1 = DetectLocation(Package_Delivery_Site);
      if (InPlace1) {
        Timer(1);
      }
    }
    Timer(2);
    if (InPlace1 && Time.RecordedTime >= 500) {
      InPlace2 = DetectLocation(Package_Delivery_Site);
    }
    if (InPlace2) {
      Stop();
      Serial.println("Found Corner");
      InPlace1 = false;
      InPlace2 = false;
      MoveRight();
      delay(3000);
      Stop();
      delay(3000);
      Level = Level + 2;
    }


  }

  while (Level == Deliver_Packages) {
  }


  while (Level == Locate_Fuel_Tank_Location) {
    read_single_sensor(Left_Back);

    if (Sensor[Left_Back].Distance >= 100) {
      MoveLeft();
    } else {
      MoveForward();
    }

    if (!InPlace1) {
      InPlace1 = DetectLocation(Fuel_Tank_Pickup);
      if (InPlace1) {
        Timer(1);
      }
    }
    Timer(2);
    if (InPlace1 && Time.RecordedTime >= 500) {
      InPlace2 = DetectLocation(Fuel_Tank_Pickup);
      Serial.println("Checking Again");
    }
    if (InPlace2) {
      Stop();
      Serial.println("Found Corner");
      InPlace1 = false;
      InPlace2 = false;
      delay(5000);
      MoveRight();
      delay(1000);
      MoveForward();
      delay(4000);
      Stop();
      Level = Level + 2;
    }
  }

  while (Level == Find_Fuel_Tanks) {
  }

  while (Level == Locate_Trench) {
    read_single_sensor(Under_Front);
    DisplayReadings(1);
    if (Sensor[Under_Front].Distance <= 100) {
      MoveBackward();
    } else {
      Stop();
      MoveForward();
      delay(500);
      Level++;
    }
  }

  while (Level == Cross_Trench) {
    read_single_sensor(Under_Back);
    read_single_sensor(Under_Front);
    read_single_sensor(Left_Back);
    if (!NearWall) {
      do {
        read_single_sensor(Left_Front);
        DisplayReadings(1);
        MoveLeft();
      } while (Sensor[Left_Front].Distance >= 45 && !NearWall);  // Get near wall

      if (!NearWall) {  // ram wall so we are even
        delay(500);
      }

      do {
        read_single_sensor(Left_Front);  // move right until we are far enough from wall
        MoveRight();
      } while (Sensor[Left_Front].Distance <= 35 && !NearWall);
    }



    NearWall = true;
    MoveBackward();

    while (Sensor[Left_Back].Distance <= 25) {
      MoveRight();
      read_single_sensor(Left_Back);
    }


    if (Sensor[Under_Front].Distance >= 70 && TrenchLevel == 0) {
      Stop();
      TurnServo(FrontCaster, FrontCaster_ID, 0, 1000);
      delay(500);
      MoveBackward();
      TrenchLevel++;
    }
    if (Sensor[Under_Back].Distance >= 70 && TrenchLevel == 1) {
      Stop();
      TurnServo(BackCaster, BackCaster_ID, 180, 1000);
      delay(500);
      TurnServo(FrontCaster, FrontCaster_ID, 180, 1000);
      delay(500);
      MoveBackward();
      TrenchLevel++;
    }
    if (Sensor[Under_Back].Distance <= 60 && TrenchLevel == 2) {
      delay(1000);
      Stop();
      TurnServo(BackCaster, BackCaster_ID, 50, 1000);
      TurnServo(FrontCaster, FrontCaster_ID, 130, 1000);
      MoveRight();
      delay(2000);
      Stop();
      TurnServo(BackCaster, BackCaster_ID, 0, 1000);
      TurnServo(FrontCaster, FrontCaster_ID, 180, 1000);
      MoveBackward();
      delay(5000);

      Level++;
    }
  }
 
  while (Level == Locate_Thrusters) {

    read_single_sensor(Back_Right);
    read_single_sensor(Right_Front);
    DisplayReadings(1);

    if (Sensor[Back_Right].Distance >= 100) {
      MoveBackward();
    } else {
      Serial.println("Near Wall");
      MoveRight();
      if (Sensor[Right_Front].Distance <= 130){
        Serial.println("Found corner");
        Stop();
        Level++;
        Level++;
      }
    }
  }

  while (Level == Build_Rocket) {
  }

  while (Level == Press_Button) {
    read_single_sensor(Back_Right);
    read_single_sensor(Left_Front);
    DisplayReadings(1);

    if (Sensor[Back_Right].Distance >= 100) {
      MoveBackward();
    } else {
      Serial.println("Near Wall");
      MoveLeft();
      if (Sensor[Left_Front].Distance <= 60){
        Serial.println("Button Pressed");
        Stop();
        Level++;
      }
    }
  }

  while (Level == Celebration) {
  }
}
