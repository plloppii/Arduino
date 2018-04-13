//www.elegoo.com
//2016.06.13

int  tempmodulePin  =  1;     // select the input  pin for  the potentiometer 
int  ledPin  =  3;   // select the pin for  the LED
int  sensorValue =  0;  // variable to  store  the value  coming  from  the sensor
int tmppin=0;
void setup()
{
pinMode(ledPin,OUTPUT);
Serial.begin(9600);
}
void loop(){
  float voltage, degreesC, degreesF;
voltage=getVoltage(tempmodulePin)/5;
degreesC=(voltage-0.5)*100.0;
degreesF=degreesC*(9.0/5.0)+32.0;
Serial.print("Voltage = ");
Serial.print(voltage,  DEC);
Serial.print(" *F ");
Serial.println(   analogRead(tempmodulePin),DEC);

float tmpV, tmpdC, tmpdF;
tmpV=getVoltage(tmppin);
tmpdC=(tmpV-0.5)*100.0;
tmpdF=tmpdC*(9.0/5.0)+32.0;
Serial.print("tmpV  = ");
Serial.print(tmpV,  DEC);
Serial.print(" *f ");
Serial.println(   analogRead(tmppin), DEC);

delay(1000);
}

float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}

