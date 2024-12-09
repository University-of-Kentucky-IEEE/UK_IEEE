
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop() {
    // put your main code here, to run repeatedly:
    int value1 =  analogRead(A0);
    Serial.print("Value 1 = ");
    Serial.print(value1);

    if ((value1 >= 503 && value1 <= 525) ) { // (value2 >= 495 && value2 <= 505) && (value3 >= 495 && value3 <= 505) && (value4 >= 505 && value4 <= 515)){
        Serial.println("  Magent NOT Detected");
        Flag.write(90);
    } else {
        Serial.println("  Magent Detected");
        Flag.write(180);
        delay(1000);
    }
    // Serial.println(value);
}
