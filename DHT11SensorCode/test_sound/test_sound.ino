
int buzzerpin=9;

void setup() {
  // put your setup code here, to run once:
pinMode(buzzerpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int delaytime=200;
  int freq=262;
tone(buzzerpin,freq,delaytime);
delay(delaytime);
}
