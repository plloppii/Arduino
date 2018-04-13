#include <Servo.h>
Servo myservoLR, myservoUD, myservoFB, myservoG;
int pot=0;
int pot1=1;
int pot2=2;
int pot3=3;
int p0;
int p1;
int p2;
int p3;

int posUD = 90;    // up down control
int posLR = 90;    // LR control
int posFB = 90;    // FB control
int posG = 90;     // grabber control
int d = 1000;
int speedDelay = 8;
int i = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(pot,OUTPUT);
pinMode(pot1,OUTPUT);
pinMode(pot2,OUTPUT);
pinMode(pot3,OUTPUT);
  myservoLR.attach(3);   // left right servo
  myservoUD.attach(5);   // up down servo
  myservoFB.attach(6);   // forward-back servo
  myservoG.attach(9);   // grabber servo
  Serial.begin(9600);          //  setup serial
  myservoLR.write(posLR);   // set LR to mid-point
  delay(d);
  myservoUD.write(posUD);  // set UD to mid-point
  delay(d);
  myservoFB.write(posFB);  // set FB to mid-point
  delay(d);
  myservoG.write(posG);  // set grabber to mid-point
}

void loop() {
  // put your main code here, to run repeatedly:
p0= analogRead(pot);
p1= analogRead(pot1);
p2= analogRead(pot2);
p3= analogRead(pot3);
posG=map(p0,0,1023,0,180);
posLR= map(p1,0,1023,0,180);
posUD= map(p2,0,1023,0,180);
posFB= map(p3,0,1023,0,180);
myservoLR.write(posLR);
myservoG.write(posG);
myservoUD.write(posUD);
myservoFB.write(posFB);
delay(100);

/*
Serial.print("POT");
Serial.print(analogRead(pot));
Serial.print(" POT1 ");
Serial.print(analogRead(pot1));
Serial.print(" POT2 ");
Serial.print(analogRead(pot2));
Serial.print(" POT3 ");
Serial.println(analogRead(pot3));*/

}
