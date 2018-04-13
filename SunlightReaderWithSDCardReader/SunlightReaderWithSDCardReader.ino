#include <Servo.h>
#include <SPI.h>
#include <SD.h>


int counts=0;
int timer1_counter;

int L1= A0;
int L2=A1;
int L3=A2;
int L4=A3;
int chipSelect=4;
int value1;
int value2;
int value3;
int value4;
int valuerecorded=0;
int howmany=0;


void setup() {
  // put your setup code here, to run once:
noInterrupts();
TCCR1A = 0;
TCCR1B = 0;
timer1_counter = 3036;
TCNT1 = timer1_counter;   // preload timer
TCCR1B |= (1 << CS12);    // 256 prescaler 
TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
interrupts();             // enable all interrupts

pinMode(L1, INPUT);
pinMode(L2, INPUT);
pinMode(L3, INPUT);
pinMode(L4,INPUT);
Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  counts++;
}


void loop() {
  // put your main code here, to run repeatedly:

String dataString = "";
    
  //Serial.println(counts);
if (counts==0){
  value1= analogRead(L1)/8;
  value2= analogRead(L2)/8;
  value3= analogRead(L3)/8;
  value4= analogRead(L4)/8;
  int sum= value1+ value2+ value3+ value4;
  int average= sum/4;
  dataString += String(average);
  dataString += ",";

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    if (howmany<=5){
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
    howmany++;
    }
    if (howmany=5){
      dataFile.println("END OF TAKING DATA");
    }
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
      }

   delay(1000);
}
if (counts>=1){
  counts=0;
}

}
