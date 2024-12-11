#define switchPin 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(switchPin, INPUT);
}
float xPos = 0;
float yPos = 0;
float GetxPos(float xPos) {
    float xReading = analogRead(1) - 510;
    if (abs(xReading) > 10) {
      xPos = xPos - xReading / 51000;
      if (xPos < 0) {
        xPos = 0;
      }
      if (xPos > 12) {
        xPos = 12;
      }
    }
    return xPos;
  }

  float GetyPos(float xPos) {
    float yReading = analogRead(0) - 503;
    if (abs(yReading) > 10) {
      yPos = yPos - yReading / 51000;
      if (yPos < 0) {
        yPos = 0;
      }
      if (yPos > 12) {
        yPos = 12;
      }
    }
    return yPos;
  }
void loop() {
  
  // // put your main code here, to run repeatedly:
  // float xReading = analogRead(1) - 510;
  // float yReading = analogRead(0) - 503;
  // // Serial.print("X = ");
  // // Serial.print(xReading/51);
  // // Serial.print("     ");
  // // Serial.print("Y = ");
  // // Serial.print(yReading/51);
  // // Serial.println();
  // if (abs(xReading) > 10) {
  //   xPos = xPos - xReading / 51000;
  //   if (xPos < 0) {
  //     xPos = 0;
  //   }
  //   if (xPos > 12) {
  //     xPos = 12;
  //   }
  // }
  // if (abs(yReading) > 10) {
  //   yPos = yPos - yReading / 51000;
  //   if (yPos < 0) {
  //     yPos = 0;
  //   }
  //   if (yPos > 12) {
  //     yPos = 12;
  //   }
  // }
  pinMode(switchPin, INPUT);
  int switchState = digitalRead(switchPin);
  while (!switchState){
    switchState = digitalRead(switchPin);
    Serial.println(switchState);
  }
  Serial.println(switchState);
  xPos = GetxPos(xPos);
  yPos = GetyPos(xPos);


//   Serial.print("xPos = ");
//   Serial.print(xPos);
//   Serial.print("     ");
//   Serial.print("yPos = ");
//   Serial.print(yPos);
//   Serial.println();
}
