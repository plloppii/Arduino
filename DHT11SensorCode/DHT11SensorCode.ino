
#include <SimpleDHT.h>
#include <math.h>
int DHT11pin=2;
int tmppin=0;
int thermistorpin=1;

const int buzzerpin=9;
const int songlength=5;
char notes[]="c c c";
int beats[] = {1,1,1,1,1};
int tempo = 300;

SimpleDHT11 dht11;
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
Serial.begin(9600);
pinMode(buzzerpin,OUTPUT);
}

void loop() {
//DHT11 CODE
byte temperatureC=0;
byte humidity=0;
double temperatureF;
  if (dht11.read(DHT11pin, &temperatureC, &humidity, NULL)) 
  {
    Serial.print("Read DHT11 failed.");
    return;
  }
temperatureF = temperatureC * (9.0/5.0) + 32.0;
Serial.print("Temperature of DHT11 =         ");
Serial.print(temperatureF);
Serial.print(" *F ");
Serial.print(temperatureC);
Serial.println(" *C ");
//Serial.print("     Humidity = ");
//Serial.print(humidity);
//Serial.println(" % ");

//TMP36GZ CODE
float voltage;
double degreesC, degreesF;
voltage=getVoltage(tmppin);
degreesC=(voltage-0.5)*100.0;
degreesF=degreesC*(9.0/5.0)+32.0;
Serial.print("Temperature of TMP36GZ =       ");
Serial.print(degreesF);
Serial.print(" *F ");
Serial.print(degreesC);
Serial.println(" *C ");


//THERMISTOR CODE           
int valF, valC;                
double tempF, tempC;            
valF=analogRead(thermistorpin);      
tempF=ThermistorF(valF);   
valC=analogRead(thermistorpin);      
tempC=ThermistorC(valC); 
if (tempC>27)
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

float getVoltage(int pin)
{
return (analogRead(pin) * 0.004882814);
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

