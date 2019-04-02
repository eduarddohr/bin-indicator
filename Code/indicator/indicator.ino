#include <SoftwareSerial.h>
#include <hx711.h>

//led
#define ledPin 12
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
  weight = scale.getGram();

  EEBlue.print("d:");
  EEBlue.println(String(distance));
  Serial.print("distance: ");
  Serial.println(distance);
  EEBlue.print("w:");
  EEBlue.println(String(weight));
  Serial.print("weight: ");
  Serial.println(weight);

  if(weight > 100)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);


  delay(1000);
  

}
