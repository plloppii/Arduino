#include <math.h>
int thermistorpin=1;
const int buzzerpin=9;
const int songlength=5;
char notes[]="c c c";
int beats[] = {1,1,1,1,1};
int tempo = 300;

double ThermistorF(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 Temp = (Temp * 9.0)/ 5.0 + 32.0; 
 return Temp;
}
double ThermistorC(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 return Temp;
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(buzzerpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int valF, valC;                
double tempF, tempC;            
valF=analogRead(thermistorpin);      
tempF=ThermistorF(valF);   
valC=analogRead(thermistorpin);      
tempC=ThermistorC(valC); 
if (tempC>39 or -)
{
 int i, duration;
 for (i=0;i<songlength;i++)
 {
  duration=beats[i]*tempo;
  if (notes[i]== ' ')
  {
    delay(duration); 
  }
  else
  {
    tone(buzzerpin,frequency(notes[i]),duration);
    delay(duration);
  }
  delay(tempo/10);
 }
}
else if (tempC<27)
{
  noTone(buzzerpin);
}

  
Serial.print("Temperature of Thermistor =    ");
Serial.print(tempF);   
Serial.print(" *F ");
Serial.print(tempC);   
Serial.println(" *C ");
delay(1000); 
}

int frequency(char note)
{
  int i;
  const int numNotes=8;
  char names[]= { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (i=0;i<numNotes;i++)
  {
    if (names[i]==note)
    {
      return (frequencies[i]);
    }
  }
  return(0);
}
