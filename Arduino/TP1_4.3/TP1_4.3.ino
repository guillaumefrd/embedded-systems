const int potentiometerPin = A0;
int value = 0; 
int count = 0;

void setup() {
  Serial.begin(9600);
  value = analogRead(potentiometerPin);
}

void loop() {
  int newValue = analogRead(potentiometerPin);
  //if there is a variation of the potentiometer, we increment the counter
  if(abs(newValue - value) > 100){
    count++;
    value = newValue;
    Serial.print("Count = ");
    Serial.println(count);
  }
}
