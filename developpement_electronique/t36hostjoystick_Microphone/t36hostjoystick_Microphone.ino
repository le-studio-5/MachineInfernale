// Joystick Logitec extreme3Dpro to teensy3.6 avec Mic PDM
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
AudioInputPDM            pdm1;           //xy=218.88888888888889,241.11111111111111
AudioEffectGranular      granular1;      //xy=372.22216796875,159.9999542236328
AudioEffectBitcrusher    bitcrusher1;    //xy=543.3333129882812,161.11109924316406
AudioOutputAnalogStereo  dacs1;          //xy=685.888916015625,246.88890075683594
AudioConnection          patchCord1(pdm1, granular1);
AudioConnection          patchCord2(granular1, bitcrusher1);
AudioConnection          patchCord3(bitcrusher1, 0, dacs1, 0);
AudioConnection          patchCord4(bitcrusher1, 0, dacs1, 1);
// GUItool: end automatically generated code
#define GRANULAR_MEMORY_SIZE 12800  // 12800 enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
#include "USBHost_t36.h"
USBHost             usbHost1;
USBHIDParser        usbHid1( usbHost1 );
JoystickController  stick( usbHost1 );
bool freeze = 0;
bool bouton[13];

void setup( ) {
  AudioMemory(40);
  usbHost1.begin();
  bitcrusher1.bits(16); /////////////////
  bitcrusher1.sampleRate(44100);
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  //granular1.beginPitchShift(25);
}

void loop() {
  usbHost1.Task();
  int Xjoy = stick.getAxis( 0 );
  int Yjoy = stick.getAxis( 1 );
  int Zjoy = stick.getAxis( 5 );
  int Cross = stick.getAxis( 9 );
  uint32_t buttons = stick.getButtons();
  for (int i = 1; i < 13; i++) { ///////////////////à tester...
    bouton[i] = (buttons >> (i - 1)) & 1;
  }
  if (bouton[2]) bitcrusher1.bits(1);
  else if (bouton[3]) bitcrusher1.bits(2);
  else if (bouton[4]) bitcrusher1.bits(3);
  else if (bouton[5]) bitcrusher1.bits(4);
  else if (bouton[6]) bitcrusher1.bits(4);
  else bitcrusher1.bits(16);
  ///////// fin à tester
  long SR =  sq(1023 - Yjoy) / 40;
  //Serial.print( buttons, BIN);
  Serial.print( Zjoy);
  Serial.println();
  bitcrusher1.sampleRate(SR);
  if (bouton[1] == 1 && freeze == 0) {
    freeze = 1;
    float msec = 10 + (1023 - Xjoy) / 2; //500.0; // + (knobA3 * 190.0);
    granular1.beginFreeze(msec);
  }
  if (bouton[1] == 0 && freeze == 1) {
    freeze = 0;
    granular1.stop();
  }
  if (bouton[12]==1 ) {
    
    granular1.beginPitchShift(10);
  }
  //
  if(freeze==1){
    float ratio;
  if (Zjoy >= 0 && Zjoy < 32) ratio = 0.25;
  if (Zjoy >= 32 && Zjoy < 96) ratio = 0.5;
  if (Zjoy >= 96 && Zjoy < 160) ratio = 1.0;
  if (Zjoy >= 160 && Zjoy < 224) ratio = 2.0;
  if (Zjoy >= 224 && Zjoy < 256) ratio = 4.0;
  //ratio = powf(2.0, (Zjoy)/255.0 * 2.0 - 1.0); // 0.5 to 2.0
  //ratio = powf(2.0, knobA2 * 6.0 - 3.0); // 0.125 to 8.0 -- uncomment for far too much range!
  granular1.setSpeed(ratio);
  }
 else{
  float pitch = Xjoy/1024.0;
  pitch=map(pitch, 0.0, 1.0, 0.75, 1.25);
  granular1.setSpeed(pitch);
 }
  delay(10);
}
