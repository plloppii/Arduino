#include <I2Cdev.h>
//#include <helper_3dmath.h>
//#include <MPU6050.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Servo.h>
long seconds=0;
int timer1_counter;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;

#define INTERRUPT_PIN 2


bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
int tiltangle;
float startdrink;
float enddrink;
float drinktime;
int pixel;
float lighttime;
bool hydrated;
unsigned long timer;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 20

#define BRIGHTNESS 15

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}



void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Setupaccelerometer();

strip.setBrightness(BRIGHTNESS);
strip.begin();
strip.show(); // Initialize all pixels to 'off'
initializeinterrupts();


}

void loop() {
  // put your main code here, to run repeatedly:
  calculatedrinktime();
  checkhydration();
  Serial.println(seconds);
}

void fadeInAndOut(uint8_t red, uint8_t green, uint8_t blue,int x) {
int b;
int i; 
int ledtime;

b=0;
while(!checkdrinking() && b<255){
       i=0;
       while(i < strip.numPixels()&& !checkdrinking()) {
          strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);
          i++;
       }
       strip.show();
       b=b+x;
  }

while(!checkdrinking() && b>0){
        i=0;
       while(i < strip.numPixels()&& !checkdrinking()) {
          strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);
          i++;
       }
       strip.show();
       b=b-x;
  }
}

void checkhydration()
{
   if (drinktime>1 && drinktime<10 && hydrated==0)
     {
        drinktime=0;
        hydrated=1;
        seconds=0;
     }
   else if (hydrated=1 && seconds<3)
   {
    fadeInAndOut(20,255,255,6);
   }
   if (seconds>=50)
     {
        hydrated=0;
        fadeInAndOut(255,75,0,2);
     }
}

void calculatedrinktime()
{
      if(checkdrinking()){
      startdrink=millis();
      while(checkdrinking())
      {
        linebounce(30);
      }
      enddrink=millis();
      drinktime=(float)(enddrink-startdrink)/1000;
      if (drinktime>1 && drinktime<10)
      {
      Serial.print("Drinktime:  ");
      Serial.println(drinktime); 
      } 
     }
}

int checkdrinking(){
  readaccelerometer();
  if (tiltangle<0 && tiltangle>-60)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void linebounce(int lighton)
{
            while((pixel<20) && (checkdrinking()))
          {
            lighttime=millis();
            while(lighttime+lighton>=millis()&&(checkdrinking()))
            {
              strip.setPixelColor(pixel,20,255,255);
              strip.show();
            }
          pixel++;
          }
          pixel=0;
          while((pixel<20) && (checkdrinking() || pixel!=20))
          {
            lighttime=millis();
            while(lighttime+lighton>=millis()&&(checkdrinking()))
            {
              strip.setPixelColor(pixel,0,0,0);
              strip.show();
            }
          pixel++;
          }
          while((pixel>0) && (checkdrinking()))
          {
            lighttime=millis();
            while(lighttime+lighton>=millis()&&(checkdrinking()))
            {
              strip.setPixelColor(pixel,10,255,255);
              strip.show();
            }
          pixel--;
          }
          pixel=20;
          while((pixel>0) && (checkdrinking()))
          {
            lighttime=millis();
            while(lighttime+lighton>=millis()&&(checkdrinking()))
            {
              strip.setPixelColor(pixel,0,0,0);
              strip.show();
            }
          pixel--;
          }
}

void initializeinterrupts()
{
    noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
    timer1_counter = 3036;
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

void readaccelerometer()
{
  if (!dmpReady) return;  //if programming failed, don't try to do anything
   mpuInterrupt = false; //reset interrupt flag
   mpuIntStatus = mpu.getIntStatus();    
   fifoCount = mpu.getFIFOCount(); // get current FIFO count
    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } 
    else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize); 
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        tiltangle= (ypr[2] * 180/M_PI);
        //Serial.println(ypr[2] * 180/M_PI);
        }
}


void Setupaccelerometer()
{
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));


    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXAccelOffset(-2663);
    mpu.setYAccelOffset(2444);
    mpu.setZAccelOffset(1045);
    mpu.setXGyroOffset(106);
    mpu.setYGyroOffset(55);
    mpu.setZGyroOffset(14);
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timer1_counter;   // preload timer
  seconds++;
}

