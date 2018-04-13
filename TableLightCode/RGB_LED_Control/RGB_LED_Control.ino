int greenPin= 6;
int redPin= 5;
int bluePin= 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  fade(bluePin);
  fade(greenPin);
  fade(redPin);
}

void fade(int led)
{
  for(int i=0; i<=255;i++){
    analogWrite(led,i);
    delay(5);
  }
  for(int i=255; i>=0; i--){
    analogWrite(led,i);
    delay(5);
  }
}

