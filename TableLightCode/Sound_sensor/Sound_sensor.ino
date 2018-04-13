int soundsensor= 0;
int soundvalue=0;
int counts=0;
int timer1_counter;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)

unsigned int sample;

int greenpin=3;
int redpin=5;
int bluepin=6;

const int numberofreadings=25;
long previousmillis=0;
int Values[numberofreadings];
int total=0;
int average=0;
int readindex=0;
int volumethreshold=100;
char energyflag=0;
char creativeflag=0;
char changeflag=0;
int fcounts;
int rcounts;
int greencounts=0;

void setup() {
  // put your setup code here, to run once:
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0;
Serial.begin(9600);
for (int thisreading=0; thisreading<numberofreadings; thisreading++){
  Values[thisreading]=0;
}
  pinMode(greenpin, OUTPUT);
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  
  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts

}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  counts++;
  fcounts++;
  rcounts++;
  greencounts++;
}


void loop() {
  // put your main code here, to run repeatedly:
   delay(2);
   soundvalue= findpeaktopeak();
   calculate_average();
   //displayreading();
   checkfade();
   checkflag();
   if (greencounts>=15){
   /// energyfade();
   }
   
   Serial.print("Total ");
   Serial.println(total);
   //Serial.print("Value");
   //Serial.println(soundvalue);
   
}
void energyfade(){
  if (energyflag==1 & creativeflag==0 & changeflag==0){
      greencounts=0;
      for(int i=0; i<=150;i++){
      analogWrite(redpin,i);
      delay(10);
      analogWrite(greenpin,255-i);
      delay(10);
     
        }
      for(int i=150; i>=0; i--){
        analogWrite(redpin,i);
        delay(10);
        analogWrite(greenpin, 255-i);
        delay(10);
        }
    }
    }
void checkfade(){
  if (average>volumethreshold){
    fcounts=0;
    while(average>volumethreshold & energyflag==0){
      soundvalue= findpeaktopeak();
      calculate_average();
       Serial.print("Total ");
      Serial.println(total);
      if (fcounts>=4){
        changeflag=1;
        checkflag();
      }
    }
  }
  if (rcounts>35 & energyflag==1){
    if (average<volumethreshold){
      //while(average<volumethreshold & creativeflag==0){
        //soundvalue= findpeaktopeak();
        //calculate_average();
        changeflag=1;
        checkflag();
      //}
    }
  }
  
}

void checkflag(){
  if(energyflag==0 & creativeflag==0){
    creativeflag=1;
    analogWrite(bluepin,  255);
  }
  else if (creativeflag==1 & energyflag==0 & changeflag==1)
  {
    fade(bluepin,greenpin);
    changeflag=0;
    creativeflag=0;
    energyflag=1;
    rcounts=0;
    greencounts=0;
  }
  else if (creativeflag==0 & energyflag==1 & changeflag==1){
    fade(greenpin,bluepin);
    changeflag=0;
    creativeflag=1;
    energyflag=0;
  }

}

void fade(int from, int to)
{
  for(int i=0; i<=255;i++){
    analogWrite(to,i);
    delay(5);
    analogWrite(from,255-i);
    delay(5);
  }
}



void calculate_average() {
   total= total-Values[readindex];
   Values[readindex]=soundvalue;
   total=total+Values[readindex];
   readindex+=1;
   if (readindex>=numberofreadings){
    readindex=0;
   average= total/numberofreadings;
   }
}

int findpeaktopeak() {
  unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   return peakToPeak;
   //double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
}

