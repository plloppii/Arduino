const int pir=7;
int pirValue;
int ledpinTHISIS=3;
int ledpinYOUR=5;
int ledpinCITY=6;

#include <SD.h>                 
#define SD_ChipSelectPin 4  
#include <TMRpcm.h> 
TMRpcm tmrpcm; 
char fileName[20];
int fileToPlay;      

void setup() {
  // put your setup code here, to run once:

    tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  return;  
  }

pinMode(pir,INPUT);
pinMode(ledpinTHISIS,OUTPUT);
pinMode(ledpinYOUR,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
digitalWrite(ledpinTHISIS,HIGH);
digitalWrite(ledpinYOUR,HIGH);
digitalWrite(ledpinCITY,HIGH);
pirValue=digitalRead(pir);
if (pirValue==1)
{
  thankyou();
  blink1();
  delay(2000);
}
}

void blink1()
{
int delaytime=200;
digitalWrite(ledpinTHISIS,LOW);
digitalWrite(ledpinYOUR,LOW);
digitalWrite(ledpinCITY,LOW);
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
digitalWrite(ledpinTHISIS,HIGH);
delay(delaytime);
digitalWrite(ledpinYOUR,HIGH);
delay(delaytime);
digitalWrite(ledpinCITY,HIGH); 

}

void thankyou()
{
 fileToPlay = random(1,13); //a random number
 sprintf(fileName, "%d.wav", fileToPlay);  //turn the number into a string and add extension
 Serial.println( fileName);
  tmrpcm.play(fileName);
}

