
#include<Bridge.h>
#include<HttpClient.h>

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  HttpClient client;
  client.get("http://www.ibo.net/");
  char previous_letter = 'a';
  int count = 0;
  while(client.available()){
    char c = client.read();
    if((c == 'o' || c == 'O') && (previous_letter == 'b' || previous_letter == 'B')){
      count++;
    }
    previous_letter = c;
    Serial.print(c);
  }

  Serial.println(" ");
  Serial.print("Count = ");
  Serial.println(count);
  
  Serial.flush();

  delay(10000);

  //Blink LED
  while(true){
    if(count < 25){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(5000);
    }
    else if(count < 50){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2500);
    }
    else if(count < 100){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
    }
    else{
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
    }
  }
  
}
