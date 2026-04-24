/*
Tremolando1.ino
Tremolo effect 
Thanks to Paul Stoffregen, www.PJRC.com, that made the great audio library fro Teensy! Plus all the other great stuff!
This code can be loaded into a Teensy3.1/3.2 with a OnkartGromt OpenEffects project platform. Use a I2C 64x128 OLED screen to show the graphics. 

All in all use the OpenEffectsProject OEP2.2 from OnkartGromt. AK4558 codec
 */

#include <Bounce.h> 
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Metro.h> 
#include "spieeprom.h"
#include "OnkartGromt_functions.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=73.01041412353516,427.99999237060547
AudioSynthWaveform       waveform2;      //xy=108.01041412353516,568.9999923706055
AudioSynthWaveformDc     dc4;            //xy=113.01041412353516,495.99999237060547
AudioSynthWaveformDc     dc6;            //xy=113.01041412353516,607.9999923706055
AudioSynthWaveformDc     dc5;            //xy=116.01041412353516,535.9999923706055
AudioSynthWaveform       waveform1;      //xy=129.01041412353516,299.99999237060547
AudioSynthWaveformDc     dc3;            //xy=133.01041412353516,334.99999237060547
AudioSynthWaveformDc     dc2;            //xy=139.01041412353516,265.99999237060547
AudioSynthWaveformDc     dc1;            //xy=140.01041412353516,233.99999237060547
AudioAnalyzePeak         peak3;          //xy=198.01041412353516,380.99999237060547
AudioFilterStateVariable filter2;        //xy=239.01041412353516,575.9999923706055
AudioFilterStateVariable filter1;        //xy=261.01041412353516,308.99999237060547
AudioEffectMultiply      multiply1;      //xy=382.01041412353516,254.99999237060547
AudioEffectMultiply      multiply2;      //xy=381.01041412353516,522.9999923706055
AudioMixer4              mixer4;         //xy=524.0104141235352,516.9999923706055
AudioMixer4              mixer3;         //xy=530.0104141235352,250.99999237060547
AudioEffectMultiply      multiply4;      //xy=652.0104141235352,479.99999237060547
AudioAnalyzePeak         peak2;          //xy=655.0104141235352,549.9999923706055
AudioEffectMultiply      multiply3;      //xy=663.0104141235352,332.99999237060547
AudioAnalyzePeak         peak1;          //xy=666.0104141235352,250.99999237060547
AudioSynthWaveformDc     dc7;            //xy=836.0103988647461,397.12153720855713
AudioMixer4              mixer2;         //xy=1018.0104141235352,444.99999237060547
AudioMixer4              mixer1;         //xy=1020.0104141235352,357.99999237060547
AudioEffectMultiply      multiply5;      //xy=1138.010440826416,386.121524810791
AudioEffectMultiply      multiply6;      //xy=1141.010440826416,425.12152099609375
AudioOutputI2S           i2s2;           //xy=1265.0102996826172,409.99998474121094
AudioConnection          patchCord1(i2s1, 0, multiply3, 1);
AudioConnection          patchCord2(i2s1, 0, mixer1, 1);
AudioConnection          patchCord3(i2s1, 0, peak3, 0);
AudioConnection          patchCord4(i2s1, 1, mixer2, 1);
AudioConnection          patchCord5(i2s1, 1, multiply4, 1);
AudioConnection          patchCord6(waveform2, 0, filter2, 0);
AudioConnection          patchCord7(dc4, 0, mixer4, 0);
AudioConnection          patchCord8(dc6, 0, filter2, 1);
AudioConnection          patchCord9(dc5, 0, multiply2, 0);
AudioConnection          patchCord10(waveform1, 0, filter1, 0);
AudioConnection          patchCord11(dc3, 0, filter1, 1);
AudioConnection          patchCord12(dc2, 0, multiply1, 0);
AudioConnection          patchCord13(dc1, 0, mixer3, 0);
AudioConnection          patchCord14(filter2, 0, multiply2, 1);
AudioConnection          patchCord15(filter1, 0, multiply1, 1);
AudioConnection          patchCord16(multiply1, 0, mixer3, 1);
AudioConnection          patchCord17(multiply2, 0, mixer4, 1);
AudioConnection          patchCord18(mixer4, 0, multiply4, 0);
AudioConnection          patchCord19(mixer4, peak2);
AudioConnection          patchCord20(mixer3, 0, multiply3, 0);
AudioConnection          patchCord21(mixer3, peak1);
AudioConnection          patchCord22(multiply4, 0, mixer2, 0);
AudioConnection          patchCord23(multiply3, 0, mixer1, 0);
AudioConnection          patchCord24(dc7, 0, multiply5, 1);
AudioConnection          patchCord25(dc7, 0, multiply6, 1);
AudioConnection          patchCord26(mixer2, 0, multiply6, 0);
AudioConnection          patchCord27(mixer1, 0, multiply5, 0);
AudioConnection          patchCord28(multiply5, 0, i2s2, 0);
AudioConnection          patchCord29(multiply6, 0, i2s2, 1);
AudioControlAK4558       ak4558;         //xy=630.0104141235352,778.9999923706055
// GUItool: end automatically generated code

//Variables for values
boolean Tap1Value = 0;
boolean Tap2Value = 0;
float Pot1Value = 512;  
float Pot2Value = 512;  
float Pot3Value = 512;  
float Pot4Value = 512;  
int SW1Value = 0;
int SW2Value = 0;
float CV1Value = 0;
float CV2Value = 0;
float Pot1ValueOld = 10;  // variable to store the previous value
float Pot2ValueOld = 10;  
float Pot3ValueOld = 10;  
float Pot4ValueOld = 10;  
int SW1ValueOld = 10;
int SW2ValueOld = 10;
int Tap1ValueOld = 1;
int Tap2ValueOld = 1;
int CV1ValueOld = 0;
int CV2ValueOld = 0;
float margin  = 7;

// Variables 
int ledStateONOFF = LOW;
int ledStateONOFF_old = HIGH;
int buttonState0;
int lastButtonState0 = LOW;

unsigned long lastDebounceTime0 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

float peak = 0.0;
float peak_2 = 0.0;
float peak_3 =0.0;
float peak_4 =0.0;
int offsetfreq = 201;
float level = 1;
float modFreqTap = 2.0;
float modFreq = 3;
float modFreqOld = 2;
float InLevel = 0;
float outLevel = 4;
float inLevel = 0.05;
float bypassLevel = 0.42;
float mixer3Level = 1.0;
float fDepth = 0.5f;
float fFreq = 0.3f;
int modWave = 0; //0=SINE,1=SAWTOOTH,2=SAWTOOTHREVERSED,3=SQUARE,4=TRIANGLE,5=ARBITRARY,6=PULSE
int stereo = 0;
float fLevel = 1.0f;
int currentBin = 0;
float Ratio = 1;
float Ratio2 = 1;
int updateFreq = 1;
int UpdateDisp = 1;
volatile unsigned long tapTime = 0;
volatile unsigned long tapTimeOld = 0;
volatile boolean flag = LOW;

//new version:
long new1, new2, new3, new4;
int SW_ENA_READ, SW_ENB_READ, SW_ENC_READ, SW_END_READ;
int encoderType = 0;


const int myInput = AUDIO_INPUT_LINEIN;


Bounce OnOff = Bounce(Tap1, 30 ); 
//Bounce BoostOnOff = Bounce(Tap2, 30); 
elapsedMillis tapInterval;  //timer that is used for tap tempo
elapsedMillis sw1Timer;

Metro resetTimer = Metro(1000);   

void setup() {
  AudioMemory(100);
  common_setup();
  SPI.setMOSI(7);
  SPI.setMISO(12);
  SPI.setSCK(14);
  
  //InLevel = float(EEPROM.read(0)/255.0);
  //outLevel = float(EEPROM.read(1));
  InLevel = 0.3;
  outLevel = 0.9;
  CORE_PIN9_CONFIG = PORT_PCR_MUX(1); // disable the clock to stop the I2S
// ...configure the codec...
  ak4558.enable();
  ak4558.enableIn();
  ak4558.enableOut();
  ak4558.volume(0.98);
  //Remember bug in volume() function. Multiply float by 255 instead of bitshift..
  //also bug in hardcoding PDN PIN.
  CORE_PIN9_CONFIG = PORT_PCR_MUX(6); // turn the I2S clock back on
  /*
  sgtl5000_1.enable();  // Enable the audio shield
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.8);
  sgtl5000_1.lineInLevel(0);   // 3.12Vp-p
  sgtl5000_1.lineOutLevel(13); // 3.16Vp-p
  sgtl5000_1.adcHighPassFilterDisable(); // reduce noise  */
  //pinMode(ledPin1, OUTPUT);
  attachInterrupt(Tap2, isrService, FALLING);
  
  mixer3.gain(0, 1);
  mixer3.gain(1, 1);
  mixer4.gain(0, 1);
  mixer4.gain(1, 1);
  mixer1.gain(0, 2);   
  mixer2.gain(0, 2);   
  mixer1.gain(1, 0);   
  mixer2.gain(1, 0);  

  dc1.amplitude(1-fDepth, 20);
  dc2.amplitude(fDepth, 20);
  dc3.amplitude(0, 20);
  dc4.amplitude(1-fDepth, 20);
  dc5.amplitude(fDepth, 20);
  dc6.amplitude(0, 20);
  
  waveform1.begin(1,fFreq,WAVEFORM_SINE);
  waveform2.begin(1,fFreq,WAVEFORM_SINE);
  waveform2.phase(0);

  filter1.frequency(40);
  filter1.resonance(0.6);  
  filter2.frequency(40);
  filter2.resonance(0.6);
   /* 
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.dacVolume (level);
  sgtl5000_1.autoVolumeControl(0,0,0,0.9,10,100);  //maxGain,response,hard limit,threshold,attack, decay
  sgtl5000_1.autoVolumeDisable();*/
 // Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();
  pixels.setPixelColor(0,yellow);
  pixels.show();
  //ledStateONOFF = EEPROM.read(6);
  ledStateONOFF_old = !ledStateONOFF;
  Serial.print("Tremolando rev3.0 20190510");
  delay(100);
  Pot4Value = analogRead(Pot4);    //Check encoder type: 0 = bourns, 1024 = oposite direction
  if (Pot4Value < 100)encoderType = 1;
  else encoderType = -1;  
}

//Main loop
void loop() {
  OnOff.update();      //update the bounce
  //BoostOnOff.update();

  // read the value from the sensor:
  Pot1Value = analogRead(Pot1);    //Level
  Pot2Value = analogRead(Pot2);    //Freq
  Pot3Value = analogRead(Pot3);    //Depth
  Pot4Value = analogRead(Pot4);    //Shape
  Tap1Value = digitalRead(Tap1);   //On off
  Tap2Value = digitalRead(Tap2);   //Mode/Tap
  SW1Value = analogRead(SW1);      //Tap Ratio
  SW2Value = analogRead(SW2);      //Mono/Stereo
  //CV1Value = analogRead(CV1);      //CV input
  //CV2Value = analogRead(CV2);      //EXP input

  if (SW1Value < 250)SW1Value = 5;   //tap ratio
  else if (SW1Value > 750)SW1Value = 1;
  else SW1Value = 3;
  
  if (SW2Value < 250)SW2Value = 5;   //stereo
  else if (SW2Value > 750)SW2Value = 1;
  else SW2Value = 3;
  
  //CV1Value = mapfloat(CV1Value, 0, 1023, 10, 1);         //ExpDepth
  //CV2Value = map(CV2Value, 0, 600, 1500, 250);           //ExpFreq

//********************ON -OFF handling**********************
  buttonState0 = OnOff.read();
  if (lastButtonState0 != buttonState0){   
      if (buttonState0 == LOW) {
        ledStateONOFF = !ledStateONOFF;
      }
  }

  // set the outputs:
if (ledStateONOFF != ledStateONOFF_old){  
  pixels.setPixelColor(2, pixels.Color(ledStateONOFF*30,(ledStateONOFF*30),ledStateONOFF*30)); // ONOFF bright white color. 
  digitalWrite(relayL, ledStateONOFF); 
  digitalWrite(relayR, ledStateONOFF); 
  ledStateONOFF_old = ledStateONOFF; 
  pixels.show(); // This sends the updated pixel color to the hardware.
 // EEPROM.write(6,ledStateONOFF);
}
  lastButtonState0 = buttonState0;

//********************SENSE handling**********************

  //read the signal input peak
 // if (peak1.available())  peak = peak1.read();
 // if (peak2.available())  peak_2 = peak2.read();    //Output peak
//  Serial.print(peak);
//  Serial.print(",p2:");
//  Serial.println(peak_2);    
  
	if (peak1.available()){
	  peak = peak1.read();
    //Serial.println(peak);
   pixels.setPixelColor(1, pixels.Color((peak)*20,(peak)*20,(peak)*20));
   pixels.show(); // This sends the updated pixel color to the hardware.
	}

  if (peak3.available()){
    //Serial.println(peak3.read());
  }
//******************** SET filter handling + expression pedal **********************  

if (SW1Value == 3) sw1Timer = 0;  // reset at center for immediate response on next press

if (SW1Value == 1 && sw1Timer > 150) {
    sw1Timer = 0;
    Ratio++;
    if (Ratio >= 5) Ratio = 1;
    fFreq = modFreqTap * (Ratio2 / Ratio);
    updateFreq = 1;
    UpdateDisp = 1;
}
if (SW1Value == 5 && sw1Timer > 150) {
    sw1Timer = 0;
    Ratio2++;
    if (Ratio2 >= 5) Ratio2 = 1;
    fFreq = modFreqTap * (Ratio2 / Ratio);
    updateFreq = 1;
    UpdateDisp = 1;
}

if (((CV1Value > CV1ValueOld+ (margin*3)) || (CV1Value < CV1ValueOld - (margin*3)))){  //Check if CVinput is active Depth
      fDepth = mapfloat(CV1Value, 500, 0, 1.0f, 0.0f);           
      dc1.amplitude(1-fDepth*.5, 20);
      dc2.amplitude(fDepth*.5, 20);
      dc4.amplitude(1-fDepth*.5, 20);
      dc5.amplitude(fDepth*.5, 20); 
      UpdateDisp = 1;  
      Serial.print("CV1:");
      Serial.println(CV1Value);
      CV1ValueOld = CV1Value;
}
if ((CV2Value > CV2ValueOld+ margin*2) || (CV2Value < CV2ValueOld - margin*2)){  //Check if exp pedal is active  //EXP Level  
    Serial.print(" CV2:");
    Serial.println(CV2Value);  
    fFreq = mapfloat(CV2Value, 0, 500, 7, 1); 
    updateFreq = 1;  
    UpdateDisp = 1;
    CV2ValueOld = CV2Value;
  }
 
if ((Pot1Value > Pot1ValueOld+ margin) || (Pot1Value < Pot1ValueOld - margin)){  //Level adjust
    //fLevel = map(Pot1Value, 0, 1023, 6,0);  
    //sgtl5000_1.lineInLevel(fLevel);   // 3.12Vp-p
    fLevel = mapfloat(Pot1Value, 0, 1023, 1.0f,.5f);
    dc7.amplitude(fLevel, 20); 

    UpdateDisp = 1;
    Pot1ValueOld = Pot1Value;
}

if ((Pot2Value > Pot2ValueOld+ margin) || (Pot2Value < Pot2ValueOld - margin)){  //Frequency values
  fFreq = mapfloat(Pot2Value, 0, 1023, 5, 0.1); 
  updateFreq = 1;  
  UpdateDisp = 1;
  Pot2ValueOld = Pot2Value;  
}

if ((Pot3Value > Pot3ValueOld+ margin) || (Pot3Value < Pot3ValueOld - margin)) {    //Depth of modulation
  fDepth = mapfloat(Pot3Value, 0, 1023, 1.0f, 0.0f);           
  dc1.amplitude(1-fDepth*.5, 20);
  dc2.amplitude(fDepth*.5, 20);
  dc4.amplitude(1-fDepth*.5, 20);
  dc5.amplitude(fDepth*.5, 20); 
  UpdateDisp = 1;
  Pot3ValueOld = Pot3Value; 
}

if ((Pot4Value > Pot4ValueOld+ margin) || (Pot4Value < Pot4ValueOld - margin)){  //Modulation Wave
  modWave = map(Pot4Value, 0, 1023, 4, 0);
  const int waveTypes[] = {WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SAWTOOTH_REVERSE, WAVEFORM_SQUARE, WAVEFORM_TRIANGLE};
  waveform1.begin(waveTypes[modWave]);
  waveform2.begin(waveTypes[modWave]);
  UpdateDisp = 1;
  Pot4ValueOld = Pot4Value;
}

if((SW2Value > SW2ValueOld+ margin) || (SW2Value < SW2ValueOld - margin))  {
  if (SW2Value == 5) waveform2.phase(0);
  else if (SW2Value == 1) waveform2.phase(180);
  UpdateDisp = 1;
  SW2ValueOld = SW2Value;
}
if (updateFreq ==1){
  waveform1.frequency(fFreq);  
  waveform2.frequency(fFreq);
  updateFreq = 0; 
  UpdateDisp = 1;
}
//********************Activate modulation handling**********************

if (tapTime  != tapTimeOld && flag == HIGH){    //interrupt detected
    flag = LOW;  
  int prevInt1 = tapInterval;                   //last tap time in millis
  int TEMPtapInterval = tapTime - tapTimeOld;           //find interval since last detected push
  Serial.println(TEMPtapInterval);
  if (TEMPtapInterval <3000 && TEMPtapInterval > 200){ 
    tapInterval = TEMPtapInterval;
    int tapIntervalAVG = (prevInt1 + tapInterval)* 0.5; //some filtering
    modFreqTap = 1/(tapIntervalAVG*0.001);
    if (modFreqTap >0.5){
      fFreq = modFreqTap *(Ratio2/Ratio);
      updateFreq = 1; 
    }
  }
    tapTimeOld = tapTime;
   // flag = LOW;
    UpdateDisp = 1;
  }
// Tap2Value high means no tap in progress
  
if (resetTimer.check()&& flag == HIGH)    flag = LOW;  

//********* Update modulation freq ********************

if(UpdateDisp == 1){
   
  //display.clearDisplay();
  display.fillRect(0,0,128,64,BLACK);  //faster then clearing screen
 // int cpuCap = AudioProcessorUsageMax();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 10);
  display.print("Depth:");
  display.print((int)(fDepth*10)); 
  display.setCursor(58, 10);
  display.print((int)Ratio2);
  display.print(":"); 
  display.print((int)Ratio);  
  display.setCursor(79, 10);
  display.print("BPM:");
  display.print(fFreq*60,0);  

   drawWaves();
   display.display(); 
   UpdateDisp = 0;
}

   Tap1ValueOld = Tap1Value;
   Tap2ValueOld = Tap2Value;   

   //AudioInterrupts();
   //AudioNoInterrupts();
 //  pixels.show();
}

void drawWaves() {
  byte w = display.width();
  byte h = display.height();
  float a = mapfloat(w / (.7 * fFreq), 18, 1828, 18, 125);

  if (modWave == 0) { // SINE — needs per-pixel loop
    for (int i = 0; i < w; i++) {
      int y = (int)(h - (40*(1-fDepth*.5) + 40*fDepth*.5*(sin(i/(3.1416*(1+.5/fFreq))))));
      display.drawPixel(i, y, WHITE);
    }
  } else if (modWave == 1) { // SAWTOOTH
    for (int j = 0; j < 10; j++) {
      display.drawLine(a*j, (20+40*fDepth), a*(j+1), 20, WHITE);
      display.drawLine(a*(j+1), (20+40*fDepth), a*(j+1), 20, WHITE);
    }
  } else if (modWave == 2) { // SAWTOOTHREVERSE
    for (int j = 0; j < 10; j++) {
      display.drawLine(a*j, 20, a*(j+1), (20+40*fDepth), WHITE);
      display.drawLine(a*(j+1), (20+40*fDepth), a*(j+1), 20, WHITE);
    }
  } else if (modWave == 3) { // SQUARE
    for (int j = 0; j < 10; j++) {
      display.drawLine(a*j, 20, a*(j+.5), 20, WHITE);
      display.drawLine(a*(j+.5), 20, a*(j+.5), (20+40*fDepth), WHITE);
      display.drawLine(a*(j+.5), (20+40*fDepth), a*(j+1), (20+40*fDepth), WHITE);
      display.drawLine(a*(j+1), (20+40*fDepth), a*(j+1), 20, WHITE);
    }
  } else if (modWave == 4) { // TRIANGLE
    for (int j = 0; j < 10; j++) {
      display.drawLine(a*j, 20, a*(j+.5), (20+40*fDepth), WHITE);
      display.drawLine(a*(j+.5), (20+40*fDepth), a*(j+1), 20, WHITE);
    }
  }
}
void isrService() {
  if (flag == LOW) {
    tapTime = millis();
    flag = HIGH;
  }
}

