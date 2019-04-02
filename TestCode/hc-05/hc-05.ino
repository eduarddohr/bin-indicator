#include <SoftwareSerial.h>
SoftwareSerial EEBlue(8, 7); // RX | TX
#define ledPin 12
int state = 0;
int c;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  EEBlue.begin(9600);   
}
void loop() {
  if (Serial.available())
    EEBlue.write(Serial.read());

  if(EEBlue.available()){
    c = EEBlue.read();
    Serial.write(c);
    if(c == '1'){
      digitalWrite(ledPin, HIGH);
    }else if(c == '0'){
      digitalWrite(ledPin, LOW);
    }
  }
}
