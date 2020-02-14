// Joystick Logitec extreme3Dpro to teensy3.6 to sérial
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=64,144
AudioSynthWaveform       waveform2;      //xy=64,210
AudioFilterStateVariable filter1;        //xy=258,158
AudioFilterStateVariable filter2;        //xy=261,235
AudioMixer4              mixer1;         //xy=496,155
AudioEffectBitcrusher    bitcrusher1;    //xy=677,157
AudioOutputAnalogStereo  dacs1;          //xy=883,162
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform2, 0, filter2, 0);
AudioConnection          patchCord3(filter1, 0, mixer1, 0);
AudioConnection          patchCord4(filter2, 0, mixer1, 1);
AudioConnection          patchCord5(mixer1, bitcrusher1);
AudioConnection          patchCord6(bitcrusher1, 0, dacs1, 0);
AudioConnection          patchCord7(bitcrusher1, 0, dacs1, 1);
// GUItool: end automatically generated code
#include "USBHost_t36.h"
USBHost             usbHost1;
USBHIDParser        usbHid1( usbHost1 );
JoystickController  stick( usbHost1 );

void setup( ) {
  AudioMemory(100);
  usbHost1.begin();
  Serial.begin( 115200 );
  waveform1.begin(WAVEFORM_SAWTOOTH);///////
  waveform1.amplitude(1);
  waveform1.frequency(440);
  waveform1.phase(0);
  waveform2.begin(WAVEFORM_SAWTOOTH);///////
  waveform2.amplitude(1);
  waveform2.frequency(440);
  waveform2.phase(0);

  filter1.frequency(2000);
  filter1.resonance(2.2); //0.7 to 5.0
  filter1.octaveControl(7); // 0 to 7
  filter2.frequency(2000);
  filter2.resonance(2.2); //0.7 to 5.0
  filter2.octaveControl(7); // 0 to 7

  mixer1.gain(0, 0.5); ///////////////////////
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0);
  mixer1.gain(3, 0);

  bitcrusher1.bits(16); /////////////////
  bitcrusher1.sampleRate(44100);
}

void loop() {
  usbHost1.Task();

  int Xjoy = stick.getAxis( 0 );
  int Yjoy = stick.getAxis( 1 );
  int Zjoy = stick.getAxis( 5 );
  int Cross = stick.getAxis( 9 );
  uint32_t buttons = stick.getButtons();
  int Ajoy = stick.getAxis( 17 );
  int Bjoy = stick.getAxis( 18 );
  int Cjoy = stick.getAxis( 19 );
//  Serial.print(Xjoy);
//  Serial.print("\t");
//  Serial.print(Yjoy);
//  Serial.print("\t");
//  Serial.print(Zjoy);
//  Serial.print("\t");
//  Serial.print(Cross);
//  Serial.print("\t");
//  Serial.print(buttons + 0x1000, BIN);

 

  waveform1.frequency(50 + (Xjoy) / 20 + (128 - Zjoy) / 50);
  waveform2.frequency(50 + (Xjoy) / 20 - (128 - Zjoy) / 50);
  filter1.frequency((1024 - Yjoy) * 2);
  filter2.frequency((1024 - Yjoy) * 2);
  if (buttons > 0) {
    byte bitc = buttons;
    bitcrusher1.bits(bitc);
  }
  else  bitcrusher1.bits(16); 
  if (Cross < 8) {
    int SR = pow(8, Cross)+40;
Serial.print(SR);  Serial.println();
    bitcrusher1.sampleRate(SR);
  }
}
