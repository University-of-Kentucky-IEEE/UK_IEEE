#include "Adafruit_VL53L0X.h"

#define TotalSensors 8

// address we will assign if multi sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define LOX5_ADDRESS 0x34
#define LOX6_ADDRESS 0x35
#define LOX7_ADDRESS 0x36
#define LOX8_ADDRESS 0x37
#define LOX9_ADDRESS 0x38
#define LOX10_ADDRESS 0x39

// set the pins to shutdown
#define SHT_LOX1 22
#define SHT_LOX2 23
#define SHT_LOX3 24
#define SHT_LOX4 25
#define SHT_LOX5 28
#define SHT_LOX6 29
#define SHT_LOX7 26
#define SHT_LOX8 27
#define SHT_LOX9 30
#define SHT_LOX10 31

#define Front_Right 0
#define Front_Left 1
#define Left_Front 2
#define Left_Back 3
#define Right_Front 4
#define Right_Back 5
#define Back_Right 6
#define Back_Left 7
#define Under_Front 8
#define Under_Back 9

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox5 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox6 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox7 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox8 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox9 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox10 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;
VL53L0X_RangingMeasurementData_t measure5;
VL53L0X_RangingMeasurementData_t measure6;
VL53L0X_RangingMeasurementData_t measure7;
VL53L0X_RangingMeasurementData_t measure8;
VL53L0X_RangingMeasurementData_t measure9;
VL53L0X_RangingMeasurementData_t measure10;

//TOF information
typedef struct {
  int LOX_ADDRESS;
  int Xshut;
  int Distance;
  String Name;
} SensorData;
SensorData Sensor[TotalSensors];



void DisplayReadings(int Pointer) {  //Displays reading (for degbugging and testing functions) reduces clutter in code and time to run commands
  switch (Pointer) {
    case 1:

      Serial.print(F("FrontL:"));
      Serial.println(Sensor[Front_Left].Distance);
      Serial.print(F("FrontR:"));
      Serial.println(Sensor[Front_Right].Distance);
      Serial.print(F("LeftFront: "));
      Serial.println(Sensor[Left_Front].Distance);
      Serial.print(F("LeftBack:"));
      Serial.println(Sensor[Left_Back].Distance);
      Serial.print(F("BackL:"));
      Serial.println(Sensor[Back_Left].Distance);
      Serial.print(F("BackR:"));
      Serial.println(Sensor[Back_Right].Distance);
      Serial.print(F("RightF:"));
      Serial.println(Sensor[Right_Front].Distance);
      Serial.print(F("RightBack:"));
      Serial.println(Sensor[Right_Back].Distance);
      //Serial.print(F("Bottom Front:"));
      // Serial.println(Sensor[Under_Front].Distance);
      // Serial.print(F("Bottom Back:"));
      // Serial.println(Sensor[Under_Back].Distance);
      Serial.println();
      break;
  }
}







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
}

void read_single_sensor(int SensorPointer) {
  switch (SensorPointer) {
    case 0:
      lox1.rangingTest(&measure1, false);                        // pass in 'true' to get debug data printout!
      if (measure1.RangeStatus != 4) {                           // if not out of range
        Sensor[Front_Left].Distance = measure1.RangeMilliMeter;  //Front Left
      }else {
        Sensor[Front_Left].Distance = 0;
      }
      break;

    case 1:
      lox2.rangingTest(&measure2, false);                             // pass in 'true' to get debug data printout!
      if (measure2.RangeStatus != 4) {                                // if not out of range
        Sensor[Left_Front].Distance = measure2.RangeMilliMeter;  //Left Front
      }else {
        Sensor[Left_Front].Distance = 0;
      }
      break;

    case 2:
      lox3.rangingTest(&measure3, false);                       // pass in 'true' to get debug data printout!
      if (measure3.RangeStatus != 4) {                          // if not out of range
        Sensor[Left_Back].Distance = measure3.RangeMilliMeter;  //Left Back
      }else {
        Sensor[Left_Back].Distance = 0;
      }
      break;

    case 3:
      lox4.rangingTest(&measure4, false);                       // pass in 'true' to get debug data printout!
      if (measure4.RangeStatus != 4) {                          // if not out of range
        Sensor[Back_Left].Distance = measure4.RangeMilliMeter;  //Back Left
      } else {
        Sensor[Back_Left].Distance = 0;
      }
      break;

    case 4:
      lox5.rangingTest(&measure5, false);                         // pass in 'true' to get debug data printout!
      if (measure5.RangeStatus != 4) {                            // if not out of range
        Sensor[Right_Front].Distance = measure5.RangeMilliMeter;  //Right Front
      }else {
        Sensor[Right_Front].Distance = 0;
      }
      break;

    case 5:
      lox6.rangingTest(&measure6, false);                         // pass in 'true' to get debug data printout!
      if (measure6.RangeStatus != 4) {                            // if not out of range
        Sensor[Front_Right].Distance = measure6.RangeMilliMeter;  //Front Right
      }else {
        Sensor[Front_Right].Distance = 0;
      }
      break;

    case 6:
      lox7.rangingTest(&measure7, false);                        // pass in 'true' to get debug data printout!
      if (measure7.RangeStatus != 4) {                           // if not out of range
        Sensor[Back_Right].Distance = measure7.RangeMilliMeter;  //Back Right
      } else {
        Sensor[Back_Right].Distance = 0;
      }
      break;

    case 7:
      lox8.rangingTest(&measure8, false);                        // pass in 'true' to get debug data printout!
      if (measure8.RangeStatus != 4) {                           // if not out of range
        Sensor[Right_Back].Distance = measure8.RangeMilliMeter;  //Right Back
      }else {
        Sensor[Right_Back].Distance = 0;
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
}

/*
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
*/
