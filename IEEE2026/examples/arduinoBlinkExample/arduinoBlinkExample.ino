// Pin number for the LED is 13
const int ledPin = 13;

// Delay time in milliseconds
const int delayTime = 1000; // 1000 ms = 1 second

void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn LED on
  digitalWrite(ledPin, HIGH);
  delay(delayTime);

  // Turn LED off
  digitalWrite(ledPin, LOW);
  delay(delayTime);
}
