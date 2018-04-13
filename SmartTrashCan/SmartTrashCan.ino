int ledpinTHISIS=11;
int ledpinYOUR=12;
int ledpinCITY=13;

void setup() {
  // put your setup code here, to run once:
pinMode(ledpinTHISIS,OUTPUT);
pinMode(ledpinYOUR,OUTPUT);
pinMode(ledpinCITY,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
blink1();
}


void blink1()
{
int delaytime=200;
digitalWrite(ledpinTHISIS,HIGH);
delay(delaytime);
digitalWrite(ledpinYOUR,HIGH);
delay(delaytime);
digitalWrite(ledpinCITY,HIGH); 
delay(delaytime);
digitalWrite(ledpinTHISIS,LOW);
digitalWrite(ledpinYOUR,LOW);
digitalWrite(ledpinCITY,LOW);
delay(delaytime);

}

