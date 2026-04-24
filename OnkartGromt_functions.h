//Pin definitions for OnkartGromt 
//

#ifndef onkartgromt_functions
#define onkartgromt_functions

#include <Encoder.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define PIN            8
#define NUMPIXELS      10
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Pinout board rev1
int Pot1 = A6;    	// select the input pin for the potentiometer
int Pot2 = A3;    	// select the input pin for the potentiometer
int Pot3 = A2;    	// select the input pin for the potentiometer
int Pot4 = A1;    	// select the input pin for the potentiometer
int CV1 = A10;		//Unused inputs directly to ADC on DSP
int CV2 = A11;		//Unused inputs directly to ADC on DSP

int Tap1 = 2;		//Left; On-Off switch
int Tap2 = 3;		//Rigth; switch- preset etc

int SW1 = A12;		//Left toggle switch
int SW2 = A13;		//Rigth toggle switch
int SWA = A16;		//Encoder Switch A (A22 not available on Teensy 4.1)
int SWB = A17;		//Encoder Switch B (A21 not available on Teensy 4.1)
int SWC = 39;		//Encoder Switch C	
int SWD = 38;		//Encoder Switch D

int relayL = 4;      // select the pin for the RelayL
int relayR = 5;      // select the pin for the RelayR

int mute = 34;
//Global common Variables

long position1 = -999;
long position2 = -999;
long position3 = -999;
long position4 = -999;

uint32_t off =pixels.Color(0,0,0);
uint32_t blue =pixels.Color(0,0,50);
uint32_t red =pixels.Color(0,50,0);
uint32_t green =pixels.Color(0,40,0);
uint32_t yellow =pixels.Color(40,40,0);
uint32_t white =pixels.Color(20,20,20);


Encoder knob1(30, 29);
Encoder knob2(28, 27);
Encoder knob3(26, 25);
Encoder knob4(24, 10);

//Common Functions:
//
void common_setup(){

  delay(100);
  pinMode(relayL, OUTPUT);
  pinMode(relayR, OUTPUT);
  pinMode(Tap1, INPUT);
  pinMode(Tap2, INPUT);  
  pinMode(SWC, INPUT);
  pinMode(SWD, INPUT);   
  pinMode(mute, OUTPUT);  
  pixels.begin();
  for (int i = 0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,off);
   } 
  pixels.show();  

  
}

//map float function
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


/* fscale
 Floating Point Autoscale Function V0.1
 Paul Badger 2007
 Modified from code by Greg Shakar

 This function will scale one set of floating point numbers (range) to another set of floating point numbers (range)
 It has a "curve" parameter so that it can be made to favor either the end of the output. (Logarithmic mapping)
*/
float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output 
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  /*
   Serial.println(curve * 100, DEC);   // multply by 100 to preserve resolution  
   Serial.println(); 
   */

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){ 
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd; 
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine 
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {   
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange); 
  }

  return rangedValue;
}

#endif