#include <Wire.h>

const int buttonPin = 7; 
const int ldrPin = A0;
byte count = 0;
int buttonState = 0;
int ldrValue = analogRead(ldrPin);


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

  Wire.begin(2);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    count++;
  }
  delay(100);
}

void requestEvent() {
  ldrValue = analogRead(ldrPin);
  byte ldrValueByte = map(ldrValue, 0, 1023, 0, 255);
  Serial.println(count);
  Serial.println(ldrValueByte);
  Wire.write(count);
  Wire.write(ldrValueByte);
}

