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
#include <FastLED.h>
CRGB leds[3];
bool freeze = 0;
bool bouton[13];
bool buttonFlag[3] = {0};

void setup( ) {
  Serial.begin(9600);
  AudioMemory(30);
  usbHost1.begin();
  bitcrusher1.bits(16); /////////////////
  bitcrusher1.sampleRate(44100);
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  //granular1.beginPitchShift(25);
  FastLED.addLeds<WS2812B, 0, GRB>(leds, 3);
//  for (int i = 0; 1 < 3; i++) {
//    leds[i].r = 255;
//    leds[i].g = 0;
//  }
//  FastLED.show();
}

void loop() {
  usbHost1.Task();
  int Xjoy = stick.getAxis( 0 );
  int Yjoy = stick.getAxis( 1 );
  int Zjoy = stick.getAxis( 5 );
  int Cross = stick.getAxis( 9 );
  uint32_t buttons = stick.getButtons();
  Serial.println("top");
  for (int i = 1; i < 13; i++) { ///////////////////à tester...
    bouton[i] = (buttons >> (i - 1)) & 1;
    Serial.println( bouton[i]);
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
  if (bouton[7] == 1 &&  buttonFlag[0] == 0) { //Boutton 7 effet 1 ON
    buttonFlag[0] = 1;
    leds[0].r = 0;
    leds[0].g = 200;
    FastLED.show();

  }
  if (bouton[8] == 1 &&  buttonFlag[0] == 1) { //Boutton 8 effet 1 OFF
    buttonFlag[0] = 0;
    leds[0].r = 255;
    leds[0].g = 0;
    FastLED.show();
  }
  if (bouton[9] == 1 &&  buttonFlag[1] == 0) { //Boutton 9 effet 2 ON
    buttonFlag[1] = 1;
    leds[1].r = 0;
    leds[1].g = 200;
    FastLED.show();

  }
  if (bouton[10] == 1 &&  buttonFlag[1] == 1) { //Boutton 10 effet 2 OFF
    buttonFlag[1] = 0;
    leds[1].r = 255;
    leds[1].g = 0;
    FastLED.show();
  }
  if (bouton[11] == 1 &&  buttonFlag[2] == 0) { //Boutton 11 effet 3 ON
    buttonFlag[2] = 1;
    leds[2].r = 0;
    leds[2].g = 200;
    FastLED.show();
    granular1.beginPitchShift(10);
  }
  if (bouton[12] == 1 &&  buttonFlag[2] == 1) { //Boutton 12 effet 3 OFF
    buttonFlag[2] = 0;
    leds[2].r = 255;
    leds[2].g = 0;
    FastLED.show();
    granular1.stop();
  }
  //
  if (freeze == 1) {
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
  else {
    float pitch = Xjoy / 1024.0;
    pitch = map(pitch, 0.0, 1.0, 0.75, 1.25);
    granular1.setSpeed(pitch);
  }
  delay(10);
}
