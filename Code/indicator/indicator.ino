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
  String print_dist=String(distance);
  weight = scale.getGram();
  String print_weight=String(weight);
 
 if(Serial.available() >0){
  incomingByte = Serial.read();
  if(incomingByte == '1'){
     if(distance<10 && weight>100){
      digitalWrite(ledPin, HIGH);
      Serial.print("Bin is full~");
     }
     else{
     Serial.print("Distance: "+print_dist+" and weight: "+print_weight+"~");
     }
  
  }   
  if(incomingByte == '0'){
     digitalWrite(ledPin, LOW);
  }
 }
 
/*
  if(weight > 100)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
 */
  delay(1000);
}
