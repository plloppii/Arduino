
#include <Servo.h>

Servo myservoLR, myservoUD, myservoFB, myservoG;  // set up servos
int posUD = 90;    // up down control
int posLR = 90;    // LR control
int posFB = 90;    // FB control
int posG = 90;     // grabber control
int d = 1000;
int speedDelay = 8;
int i = 0;

void setup()

{
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

void loop()

{
  delay(50);

  while( i<80){
    myservoLR.write(posLR);
    myservoUD.write(posUD);
    myservoFB.write(posFB);
    posLR = posLR+1;
    posUD = posUD+1;
    posFB = posFB+1;
    i++;
    delay(speedDelay);
  }
  i = 0;
  while( i<80){
    myservoLR.write(posLR);
    myservoUD.write(posUD);
    myservoFB.write(posFB);
    posLR = posLR-1;
    posUD = posUD-1;
    posFB = posFB-1;
    i++;
    delay(speedDelay);
  }
  /*
  // move left right
  for (posLR; posLR <= 170; posLR += 1) { // goes from 90 degrees to 140 degrees
    // in steps of 1 degree
    myservoLR.write(posLR);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
   // Serial.println(posLR);
  }
 
  for (posLR; posLR >= 10; posLR -= 1) { // goes from 140 degrees to 30 degrees
    myservoLR.write(posLR);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
   // Serial.println(posLR);
  }
    
  // move up down
  for (posUD; posUD <= 170; posUD += 1) { // goes from 90 degrees to 140 degrees
    // in steps of 1 degree
    myservoUD.write(posUD);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
   // Serial.println(posUD);
  }

  for (posUD; posUD >= 90; posUD -= 1) { // goes from 140 degrees to 30 degrees
    myservoUD.write(posUD);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
    //Serial.println(posUD);
  }
  
  // move forward back
  for (posFB ; posFB <= 170; posFB += 1) { // goes from 90 degrees to 140 degrees
    // in steps of 1 degree
    myservoFB.write(posFB);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
    //Serial.println(posFB);
  }
  for (posFB; posFB >= 90; posFB -= 1) { // goes from 140 degrees to 30 degrees
    myservoFB.write(posFB);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
    //Serial.println(posFB);
  }
  
  // move grabber
  for (posG; posG <= 160; posG += 1) { // goes from 90 degrees to 140 degrees
    // in steps of 1 degree
    myservoG.write(posG);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
    //Serial.println(posG);
  }
  for (posG; posG >= 10; posG -= 1) { // goes from 140 degrees to 30 degrees
    myservoG.write(posG);              // tell servo to go to position in variable 'pos'
    delay(speedDelay);                       // waits 15ms for the servo to reach the position
    //Serial.println(posG);
  }
  */
  delay(d);
  

  //  delay(15);

  
}
 
