//initalize global variables and structures
#define TODO 0
#define TotalSensors 10
#define TotalServos 13



//LED STARTUP
int InPlaceLevel = 0;
bool InPlace1 = false;
bool InPlace2 = false;
const int photoRpin = A1;  // pin of the photoresistor
bool loopFlag = 0;
unsigned int prevAvg;
unsigned int curAvg;
int TrenchLevel = 0;
bool NearWall = false;


String SideTilt;
int SideDif;

int Stored_Small_Packages = 0;
int Stored_Large_Packages = 0;
int Stored_Fuel_Tanks = 0;


typedef struct {
  float temp;
  float RecordedTime;
} TimeReading;
TimeReading Time;

//
//
// LEVEL SYSTEM
//
//

int Level = -1;
#define LED_Startup 0
#define Find_Large_Packages 1
#define Find_Small_Packages 2
#define Locate_Package_Delivery_Site 3
#define Deliver_Packages 4
#define Locate_Fuel_Tank_Location 5
#define Find_Fuel_Tanks 6
#define Locate_Trench 7
#define Cross_Trench 8
#define Locate_Thrusters 9
#define Build_Rocket 10
#define Press_Button 11
#define Celebration 12



//
//
// TOF SETUP
//
//


/*
0,1 Front 
2,3 Left
4,5 Right
6,7 Back
8 Lower Front
9 Lower Back
*/

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

//Locations
#define Package_Delivery_Site 0
#define Fuel_Tank_Pickup 1
#define Trench_Start 2
#define Tench_Middle 3
#define Tench_End 4
#define Rocket_Assembly 5
#define Button 6

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

//
// SERVO SETUP
//
//Servo Speeds
#define Stall 1500
#define MaxPulse 2500
#define MinPulse 500

//Servo Names for servo structure (only used for Non-continuous servos)
// #define ArmBase 0
// #define Elbow1 1
// #define Elbow2 2
// #define Wrist 3
// #define Grabber 4
// #define Test 5


//servo Pins
#define BaseServo_ID 0
#define ArmBase_ID 1
#define Elbow1_ID 2
#define Elbow2_ID 3
#define Wrist_ID 4
#define Grabber_ID 5
#define FrontCaster_ID 6
#define BackCaster_ID 7  //Back caster servo
#define FR_ID 8          //front right servo
#define BR_ID 9          //back right servo
#define FL_ID 10         //front left servo
#define BL_ID 11         //back left servo
#define PixyCam_ID 12



Servo BaseServo;
Servo ArmBase;
Servo Elbow1;
Servo Elbow2;
Servo Wrist;
Servo Grabber;
Servo FrontCaster;
Servo BackCaster;
Servo FR;  //front right servo
Servo BR;  //back right servo
Servo FL;  //front left servo
Servo BL;  //back left servo
Servo PixyCam;

//Turn base turnning raduis
#define MAX_BASE_ANGLE 330
#define MIN_BASE_ANGLE 2
float CurrentBaseAngle = 0;

//Servo Info
typedef struct {
  int Pin;
  int CurrentPosition;
  int MinAngle;
  int MaxAngle;
} ServoInfo;
ServoInfo ServoType[TotalServos];



//
//
// PIXY2 VARIABLES
//
//


//NEEDS TESTING
//Block width at 250 mm
#define Large_Package_Width 4
#define Small_Package_Width 2
#define Fuel_Tank_Width 2
#define Thruster_Width 3


//Change to fix object distance calculation
#define Focal_Length 50
#define PixyImageCenter 158
#define PixelOffset 25  //pixel offset from middle used for accuracy
int WantedObject;
