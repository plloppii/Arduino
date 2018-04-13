#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8); // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
long capacitance=0;
long sum;
long average;



void setup()                    
{
   cs_4_8.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   /*
   for (int i=0; i<800;i++)
   {
    sum+=cs_4_8.capacitiveSensor(1);
    Serial.println(sum);
    i++;
   }
   */
   average=sum/800;
   Serial.println("average");
   Serial.println(average);
}
/*
int checkdrinking(){
  if ((tiltangle<0 && tiltangle>-60)&& cs_4_8.capacitiveSensor(20)>1000)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
*/


void loop()                    
{
  
  capacitance=cs_4_8.capacitiveSensor(2);
    
    Serial.println(capacitance);  // print sensor output 

}
