#include <SD.h>                      // need to include the SD library 
//using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

unsigned long time = 0;
int SD_ChipSelectPin=4;

void setup(){
int tmrpcm.speakerPin = 9; 
 pinMode(9,OUTPUT); //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45 

  Serial.begin(115200);
  if (SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not

  }
  else{   
    Serial.println("SD ok");   
  }
  tmrpcm.play("81"); //the sound file "music" will play each time the arduino powers up, or is reset
}



void loop(){  

  //blink the LED manually to demonstrate music playback is independant of main loop
  if(tmrpcm.isPlaying() && millis() - time > 50 ) {      
      digitalWrite(13,!digitalRead(13));
      time = millis();    
  }else
  if(millis() - time > 500){     
    digitalWrite(13,!digitalRead(13)); 
    time = millis(); 
  }


  if(Serial.available()){    
    switch(Serial.read()){
    case 'd': tmrpcm.play("music"); break;
    case 'P': tmrpcm.play("temple"); break;
    case 't': tmrpcm.play("catfish"); break;
    case 'p': tmrpcm.pause(); break;
    case '?': if(tmrpcm.isPlaying()){ Serial.println("A wav file is being played");} break;
    case 'S': tmrpcm.stopPlayback(); break;
    case '=': tmrpcm.volume(1); break;
    case '-': tmrpcm.volume(0); break;
    case '0': tmrpcm.quality(0); break;
    case '1': tmrpcm.quality(1); break;
    default: break;
    }
  }

}
