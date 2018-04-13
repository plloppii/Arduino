#include <SD.h>                 
#define SD_ChipSelectPin 4  
#include <TMRpcm.h>         
 
TMRpcm tmrpcm; 
char fileName[20];
int fileToPlay;
void setup(){

  tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  return;   // don't do anything more if not
  }
 tmrpcm.volume(7);
 tmrpcm.play("1.wav"); //the sound file "1" will play each time the arduino powers up, or is reset
 Serial.begin(9600);

}
 
void loop(){ 
 int delaytime=5000;
 fileToPlay = random(1,4); //a random number
 sprintf(fileName, "%d.wav", fileToPlay);  //turn the number into a string and add extension
 Serial.println( fileName);
  tmrpcm.play(fileName);
  delay(delaytime);
    }

 
 
  
