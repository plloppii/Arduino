// This is a simple working-example to quick measuring:
// 1. the x, y and z-values read from a GY-61-acceleration-module
// 2. an angle in eg. the x-direction

// You can put the module in 4 directions to determine the min-max-values:
// –>   0deg   x = 349  y = 341  z = 425
// /\    90deg  x = 281  y = 345  z = 357
// <–  180deg  x = 350  y = 345  z = 288
//  V   270deg  x = 419  y = 341  z = 355
// This can be used to measure degrees

// you can use all the analog inputs to control the GY-61
// picture: https://www.fabtolab.com/ADXL335-GY61?search=gy-61
#include <Servo.h>
int servoPinx=9;
int servoPiny=10;
Servo servox;
Servo servoy;
int servoAnglex=0;
int servoAngley=0;

int lasty;
int lastx;
signed int xchange;
signed int ychange;

const int xPin   = A0;
const int yPin   = A1;
const int zPin   = A2;
int yangle;
int xangle;


// variables
int x = 0;
int y = 0;
int z = 0;

void setup() {
// pin A0 (pin14) is VCC and pin A4 (pin18) in GND to activate the GY-61-module
//pinMode(A0, OUTPUT);
//pinMode(A4, OUTPUT);
//digitalWrite(14, HIGH);
//digitalWrite(18, LOW);
 servox.attach(servoPinx);
 servoy.attach(servoPiny);
// activating debugging for arduino UNO
Serial.begin(9600);
} // end setup

void loop() {
x = analogRead(xPin);
y = analogRead(yPin);
xchange= abs(lastx-x);
ychange= abs(lasty-y);

while (xchange>=10 | ychange >=10){
  x=analogRead(xPin);
  xchange= abs(lastx-x);
  lastx=x;
  y=analogRead(yPin);
  ychange= abs(lasty-y);
  lasty=y;
  Serial.println(xchange);
  delay(30);
}

//lastx=x;
//lasty=y;

servoAngley=constrain(map(x,395,264,45,135),40,140); //map y angle to the y servo angle (45-135 degrees).
servoAngley= 180-servoAngley; //flip the direction of the y servo
Serial.print("Servoangley=");
Serial.print(servoAngley);
servoy.write(servoAngley);

servoAnglex=constrain(map(y,395,264,45,135),40,140); //map x angle to the y servo angle (45-135 degrees).

Serial.print("Servoanglex=");
Serial.println(servoAnglex);
servox.write(servoAnglex);

delay(80);

} // end loop
