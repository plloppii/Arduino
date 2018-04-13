int button1=2;
int button2=3;
int button3=4;
int button4=5;
int button5=6;
int LED=7;
int delaytime;
int winner;
unsigned long turnontime;
int allpressed;
unsigned long t1;
unsigned long t2;
unsigned long t3;
unsigned long t4;
float rt1;
float rt2;
float rt3;
float rt4;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(button1, INPUT);
pinMode(button2, INPUT);
pinMode(button3, INPUT);
pinMode(button4, INPUT);
pinMode(button5, INPUT);
pinMode(LED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
allpressed=0;
t1=0;
t2=0;
t3=0;
t4=0;
digitalWrite(LED,LOW);
while(digitalRead(button1)==0){
  delay(10);
}
delaytime=random(1000,7500);
delay(delaytime);
digitalWrite(LED,HIGH);
turnontime=millis();
//Serial.println(turnontime);
while (allpressed==0){
  if(digitalRead(button2)==1)
  {
    if(t1==0){
    t1=millis()-40;
    }
  }
  if(digitalRead(button3)==1)
  {
    if(t2==0){
    t2=millis()-40;
    }
  }
  if(digitalRead(button4)==1)
  {
    if(t3==0){
    t3=millis()-40;
    }
  }
  if(digitalRead(button5)==1)
  {
    if(t4==0){
    t4=millis()-40;
    }
  }
  delay(10);
  checkallpressed();
}
Serial.println("Reaction times");
rt1= (float)(t1-turnontime)/1000.00;
rt2= (float)(t2-turnontime)/1000.00;
rt3= (float)(t3-turnontime)/1000.00;
rt4= (float)(t4-turnontime)/1000.00;
Serial.print("Player 1: ");
Serial.print(rt1);
Serial.print(" Player 2: ");
Serial.print(rt2);
Serial.print(" Player 3: ");
Serial.print(rt3);
Serial.print(" Player 4: ");
Serial.println(rt4);

}

void checkallpressed(){
  if (t1!=0 & t2!=0 & t3!=0 & t4!=0){
    allpressed=1;
  }
}
void debounce(){
  delay(40);
}

