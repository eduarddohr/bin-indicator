#include <SoftwareSerial.h>
#include <hx711.h>

//led
#define ledPin 12
//bluetooth
#define rxPin 1
#define txPin 0
//distance
#define trigPin 2
#define echoPin 3
//weigth
#define dtPin A2 
#define sckPin A3

  SoftwareSerial EEBlue(rxPin, txPin);
  Hx711 scale(dtPin, sckPin);
  char incomingByte;

long calculateDistance(){
  long duration, cm;
  int goodRead = 0;
  while(goodRead == 0){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    cm = duration*0.034/2;
    if(cm < 300)
      goodRead = 1;
  }
  return cm;   
}

void setup() {
  Serial.begin(9600);
  //bluetooth
  EEBlue.begin(9600);  
  //distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  //led
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int distance = 0;
  int weight = 0;

  distance = calculateDistance();
  String afisaj=String(distance)+"~";
  //weight = scale.getGram();

 if(Serial.available() >0){
  incomingByte = Serial.read();
  if(incomingByte == '1'){
     digitalWrite(ledPin, HIGH);
     /*
     //incerc sa las sa se afiseze mai multe distante
     int ok=10;
     String sfarsit="~";
     while(ok>0){
      distance = calculateDistance();
      String afisaj = String(distance);
      Serial.print(afisaj);
      Serial.print("\n");
      ok--;
      //delay(1000);
     }
     */
     Serial.print(afisaj);
  }
  if(incomingByte == '0'){
     digitalWrite(ledPin, LOW);
  }
 }
 /*
  EEBlue.print("w:");
  EEBlue.println(String(weight));
  Serial.print("weight: ");
  Serial.println(weight);

  if(weight > 100)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
  */
  delay(1000);
}
