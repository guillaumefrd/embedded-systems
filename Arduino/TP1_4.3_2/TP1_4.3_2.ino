const int interruptPin = 2; 
int count = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), printCount, CHANGE);
}

void loop() {
  
}

void printCount() {
  count++;
  Serial.print("Count = ");
  Serial.println(count);
}

