#include <SoftwareSerial.h>
#include <hx711.h>

//led
#define ledPin 5
//bluetooth
#define rxPin 8
#define txPin 7
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
    if(cm < 30)
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
  
  EEBlue.print(print_dist+" "+print_weight+"~");
  float cD = 90 - (distance * 5);
  float cW = (float) (weight * 0.05);
  float Capacity = max(cD, cW);
  

  if(Capacity > 80){
      digitalWrite(ledPin, HIGH);
    }
    else
      digitalWrite(ledPin, LOW);
  Serial.println("Distance: "+print_dist+" and weight: "+print_weight+"~");
 // EEBlue.println("Distance: "+print_dist+" and weight: "+print_weight+"~");
 
  delay(3000);
}
