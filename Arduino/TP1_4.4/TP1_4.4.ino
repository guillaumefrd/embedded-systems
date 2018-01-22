int ldrPin = A0;
int sensorMin = 1023; 
int sensorMax = 0;
int ldrValue = analogRead(ldrPin);

void setup() {
  Serial.begin(9600);
  calibration();
}

void loop() {
  ldrValue = analogRead(ldrPin);
  Serial.print("LDR value = "); 
  ldrValue = map(ldrValue, sensorMin, sensorMax, 0, 255);
  Serial.println(ldrValue); 
  delay(1000);
}

void calibration() {
  while(!Serial){}
  Serial.println("Calibration starting");
  //calibration
  while(millis() < 5000) {
      ldrValue = analogRead(ldrPin);
      //record the maximum sensor value
      if(ldrValue > sensorMax) {
        sensorMax = ldrValue; 
      }
      // record the minimum sensor value
      if (ldrValue < sensorMin) {
        sensorMin = ldrValue;
      }
  }
  Serial.println("Calibration finished");
}

