int pin=0;
int knob;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
knob= analogRead(pin);
Serial.println(knob);
delay(150);
}
