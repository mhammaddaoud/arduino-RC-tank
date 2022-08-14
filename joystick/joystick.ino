#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TMright pin, HC-12 RMright pin

#define Set 12   //HC-12 set pin

String str = "o";
String test = "";
int RL = 0;
int FB = 0;
int V = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //initialize serial
  
  HC12.begin(9600);   //initialize HC-12

  //joystick pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(Set, OUTPUT);
  digitalWrite(Set, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Set, HIGH);
  str = "o";

  RL = analogRead(A0);
  FB = analogRead(A1);
  if (RL >= 510 && RL <= 520 && FB >= 500 && FB <= 510) { // stop
    V = 0;
    str += "S";
    str += V;
    str += "n";
  } else if (RL < 510 && RL >= 0 && FB >= 200 && FB <= 800) { // left
    V = map(RL, 509, 0, 0, 255);
    str += "L";
    str += V;
    str += "n";
  } else if (RL > 520 && RL <= 1023 && FB >= 200 && FB <= 800) { // right
    V = map(RL, 521, 1023, 0, 255);
    str += "R";
    str += V;
    str += "n";
  }

  else if (RL >= 400 && RL <= 600 && FB > 510 && FB <= 1023) { // forward
    V = map(FB, 511, 1023, 0, 255);
    str += "F";
    str += V;
    str += "n";
  } else if (RL >= 400 && RL <= 600 && FB < 500 && FB >= 0) { // backward
    V = map(FB, 499, 0, 0, 255);
    str += "B";
    str += V;
    str += "n";
  }

  //conditions so HC-12 sends only new commands
  if (str != test) {
    HC12.print(str);
    str = test;
  } else {
    str = test;
  }
  delay(10);
}
