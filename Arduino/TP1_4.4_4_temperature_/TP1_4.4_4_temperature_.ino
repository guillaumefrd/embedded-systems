int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  while(!Serial){}
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * 5.0;
  voltage /= 1024;
  float temp = (voltage - 0.5) * 100;
  Serial.print("Temperature = ");
  Serial.println(temp); 
  delay(1000);
}
