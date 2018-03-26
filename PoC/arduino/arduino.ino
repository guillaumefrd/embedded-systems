#include <dht.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Bridge.h>
#include <HttpClient.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensorLDRPin = A0;
int sensorLDRValue = 0;
int pinLED = 8;
int countTime = 0;
int servoPos = 0;
Servo myservo1;
Servo myservo2;
dht DHT;
#define DHT11_PIN 7

void setup() {
  lcd.begin(16, 2);
  pinMode(pinLED, OUTPUT);
  myservo1.attach(9);
  myservo2.attach(6);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  digitalWrite(13, LOW);
  delay(10000);
}

void loop() { 
  //Send data to server every 10 seconds
  if(countTime > 10) {
    sendData(DHT.temperature, DHT.humidity, sensorLDRValue);
    countTime = 0;
  }
  
  updateValues();
  analyseValues();
  printLCD(1, DHT.temperature);
  delay(1000);
  
  updateValues();
  analyseValues();
  printLCD(2, DHT.humidity);
  delay(1000);

  updateValues();
  analyseValues();
  printLCD(3, sensorLDRValue);
  delay(1000);
  
  countTime += 3;
}

// ----- Update the values ----- //

// update the values of luminosity, temperature and humidity
void updateValues() {
  DHT.read11(DHT11_PIN);
  sensorLDRValue = analogRead(sensorLDRPin);
}

// ----- Analyse the values ----- //

// main function to analyse the values of luminosity, temperature and humidity
void analyseValues() {
  analyseLuminosity(sensorLDRValue);
  analyseHumidity(DHT.humidity);
  analyseTemparature(DHT.temperature);
}

// analyse luminosity: turn on the LED if the luminosity is greater than 600
void analyseLuminosity(int value) {
  if(value < 600) {
    digitalWrite(pinLED, HIGH);
    sendMessage(3);
  }
  else {
    digitalWrite(pinLED, LOW);
  }
}

// analyse humidity: if the humidity is bellow 10%, we call the function putWater()
void analyseHumidity(int value) {
  if (value < 10) {
    putWater();
    sendMessage(2);
  }
}

// analyse temperature: if the temperature is higher than 25°C, we call the function activateFan()
void analyseTemparature(int value) {
  if (value > 30) {
    activateFan(); 
    sendMessage(1);
  }
}

// ----- Servos ----- //

// simulate the action of putting water by actionning a servo, which symbolize a water pump
void putWater() {
  for (servoPos = 0; servoPos <= 180; servoPos += 1) { 
    myservo1.write(servoPos);              
    delay(15);     
  }
}

// simulte the action of activating a fan by making a servo turn 
void activateFan() {
  for (servoPos = 0; servoPos <= 180; servoPos += 1) { 
    myservo2.write(servoPos);              
    delay(5);     
  }
  for (servoPos = 180; servoPos >= 0; servoPos -= 1) { 
    myservo2.write(servoPos);              
    delay(5);     
  }
}

// ----- Display Values (LCD) ----- //

void printLCD(int typeValue, int value) {
  if(typeValue == 1) { //display temperature 
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Temparture");
    lcd.setCursor(0,1);
    lcd.print(value);
    lcd.print((char)223);
    lcd.print("C");
  } 
  else if (typeValue == 2) { //display humidity 
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Humidity");
    lcd.setCursor(0,1);
    lcd.print(value);
    lcd.print("%");
  } 
  else if (typeValue == 3) { //display luminosity 
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Luminosity");
    lcd.setCursor(0,1);
    lcd.print(value);
  }
}

//Send data to server
void sendData(int temp, int hum, int lum) {  
  char data[100];
  char string1[25] = "{\"temperature\":";
  char string2[25] = ",\"humidity\":";
  char string3[25] = ",\"luminosity\":";
  char string4[25] = "}";
  
  sprintf(data, "%s%i%s%i%s%i%s", string1, temp, string2, hum, string3, lum, string4);
  
  HttpClient client;
  client.setHeader("Content-Type: application/json");
  client.post("http://192.168.43.194:3000/data", data);
}

void sendMessage(int typeValue) {  
  HttpClient client;
  client.setHeader("Content-Type: application/json");

  if(typeValue == 1) { //send notification about temperature 
    client.post("http://192.168.43.194:3000/message", "{\"message\":\"temperature is too high, the fan has been activated\"}");
  }
  else if (typeValue == 2) { //send notification about humidity
    client.post("http://192.168.43.194:3000/message", "{\"message\":\"humidity is too low, some water has been dropped\"}"); 
  }
  else if (typeValue == 3) { //send notification about luminosity
    client.post("http://192.168.43.194:3000/message", "{\"message\":\"luminosity is too low, the LED has been turned on\"}"); 
  }
}
