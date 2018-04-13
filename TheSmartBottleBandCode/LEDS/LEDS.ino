
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 20

int BRIGHTNESS=25;
int brightness;
int waitTime=1;
int t1;
int t2;
uint8_t b;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int t=50;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  strip.setBrightness(BRIGHTNESS);
 strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  t1=millis();
  strip.setPixelColor(0,255,255,255);
  strip.setPixelColor(1,255,255,255);
  strip.setPixelColor(2,255,255,255);
  strip.setPixelColor(3,255,255,255);
  strip.setPixelColor(4,255,255,255);
  strip.setPixelColor(5,255,255,255);
  strip.setPixelColor(6,255,255,255);
  strip.setPixelColor(7,255,255,255);
  strip.setPixelColor(8,255,255,255);
  strip.setPixelColor(9,255,255,255);
  strip.setPixelColor(10,255,255,255);
  strip.setPixelColor(11,255,255,255);
  strip.setPixelColor(12,255,255,255);
  strip.setPixelColor(13,255,255,255);
  strip.setPixelColor(14,255,255,255);
  strip.setPixelColor(15,255,255,255);
  strip.setPixelColor(16,255,255,255);
  strip.setPixelColor(17,255,255,255);
  strip.setPixelColor(18,255,255,255);
  strip.setPixelColor(19,255,255,255);
  strip.setPixelColor(20,255,255,255);
  
  strip.show();
  t2=millis();
  Serial.println(t2-t1);
}
/*
void fadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
b=0;
while(!checkdrinking() && b<255){
    t1=millis();
    while(t1+3>millis()&& checkdrinking()) {
       while(i < strip.numPixels()&& checkdrinking()) {
          strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);
          i++;
       }
       strip.show();
    }
    b++;
  }

while(!checkdrinking() && b>0){
    t1=millis();
    while(t1+3>millis()&& checkdrinking()) {
       while(i < strip.numPixels()&& checkdrinking()) {
          strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);
          i++;
       }
       strip.show();
    }
    b--;
  }

}

*/




void flashlights(){

  // put your main code here, to run repeatedly:
  for (int i=0;i<20;i++){
    unsigned long t1= millis();
    while(t1+t>=millis())
    {
      strip.setPixelColor(i,100,100,255);
      strip.show();
      Serial.println(t1+t);
    }
  }
  for (int j=20;j>=0;j--)
  {
    unsigned long t1=millis();
    while(t1+t>=millis())
    {
    strip.setPixelColor(j,0,0,0);
    strip.show();
    Serial.println(t1+t);
    }
  }
}
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
