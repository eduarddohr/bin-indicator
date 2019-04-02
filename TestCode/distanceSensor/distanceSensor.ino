int trigPin = 2;    // Trigger
int echoPin = 3;    // Echo

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
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("distance: ");
  Serial.println(calculateDistance());
  delay(500);
}
