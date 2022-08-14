#include<SoftwareSerial.h>

//////////////MOTORS PINS//////////////
#define rightF 3   //right forward motor
#define rightB 5   //right back motor

#define leftB 6    //left back motor
#define leftF 9    //left forward motor
///////////////////////////////////////

#define Set 12    //HC-12 SET pin

SoftwareSerial HC12(10, 11); //HC-12 TX pin, HC-12 RX pin

char incoming;

String mystr = "";
String str = "";
String Lstr = "";
String Rstr = "";
String Fstr = "";
String Bstr = "";
int LINT = 0;
int RINT = 0;
int FINT = 0;
int BINT = 0;

bool start = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //initialize serial

  HC12.begin(9600); //initialize HC-12 module


//////////////MOTORS PINS MODE//////////////
  pinMode(rightF, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(leftF, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(Set, OUTPUT);
  ///////////////////////////////////////

  digitalWrite(Set, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Set, HIGH);
  while (HC12.available()) { //check if data is available from the joystick
    incoming = HC12.read();
    //message from joystick start with o and ends with n
    if (incoming == 'o') {
      start = true;
    }

    if (start == true) {
      if (incoming != 'n') {
        mystr += incoming;
        delay(1);
      }
      else if (incoming == 'n') {
        start = false;
        break;
      }
    }
  }

  mystr.remove(0, 1); //RXX or LXX or FXX or BXX
  str = mystr;
  str.remove(1); // L or R or F or B
  if (str == "L") {
    Lstr = mystr; // LXX
    Lstr.remove(0, 1); //XX
    LINT = Lstr.toInt();
    motors(LINT, 0, 0, LINT);
  }
  else if (str == "R") {
    Rstr = mystr; //RXX
    Rstr.remove(0, 1); //XX
    RINT = Rstr.toInt();
    motors(0, RINT, RINT, 0);
  }
  else if (str == "F") {
    Fstr = mystr; //FXX
    Fstr.remove(0, 1); //XX
    FINT = Fstr.toInt();
    motors(FINT, 0, FINT, 0);
  }
  else if (str == "B") {
    Bstr = mystr; //BXX
    Bstr.remove(0, 1); //XX
    BINT = Bstr.toInt();
    motors(0, BINT, 0, BINT);
  }
  else if (str == "S") {
    motors(0, 0, 0, 0);
  }
  mystr = "";
}

void motors (int RF, int RB, int LF, int LB) {
  analogWrite(rightF, RF);
  analogWrite(rightB, RB);
  analogWrite(leftF, LF);
  analogWrite(leftB, LB);
}
