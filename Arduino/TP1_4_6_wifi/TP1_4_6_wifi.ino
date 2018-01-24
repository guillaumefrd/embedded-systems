
#include<Bridge.h>
#include<HttpClient.h>

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  HttpClient client;
  client.get("http://www.ibo.net/");
  char lettre_precedente = 'a';
  int count = 0;
  while(client.available()){
    char c = client.read();
    if((c == 'o' || c == 'O') && (lettre_precedente == 'b' || lettre_precedente == 'B')){
      count++;
    }
    lettre_precedente = c;
    Serial.print(c);
  }

  Serial.print("Count = ");
  Serial.println(count);
  
  Serial.flush();

  delay(10000);
}
