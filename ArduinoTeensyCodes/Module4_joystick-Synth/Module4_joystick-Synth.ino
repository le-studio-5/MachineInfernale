#include <Audio.h>

AudioSynthWaveform       lfo;      //xy=241,194
AudioSynthNoiseWhite     noise;         //xy=243,111
AudioSynthWaveformDc     shapeosc;            //xy=392,260
AudioMixer4              mixerfm;         //xy=471,89
AudioSynthWaveformModulated trisaw;   //xy=626,144
AudioMixer4              mixerfilter;         //xy=630,210
AudioFilterStateVariable filter;        //xy=809,157
AudioEffectFreeverb      freeverb;      //xy=908,240
AudioMixer4              mixer;         //xy=1018,163
AudioOutputAnalogStereo  dacs;          //xy=1197,163
AudioConnection          patchCord1(lfo, 0, mixerfm, 1);
AudioConnection          patchCord2(lfo, 0, mixerfilter, 1);
AudioConnection          patchCord3(noise, 0, mixerfm, 0);
AudioConnection          patchCord4(noise, 0, mixerfilter, 0);
AudioConnection          patchCord5(shapeosc, 0, trisaw, 1);
AudioConnection          patchCord6(mixerfm, 0, trisaw, 0);
AudioConnection          patchCord7(trisaw, 0, filter, 0);
AudioConnection          patchCord8(mixerfilter, 0, filter, 1);
AudioConnection          patchCord9(filter, 0, freeverb, 0);
AudioConnection          patchCord10(filter, 0, mixer, 0);
AudioConnection          patchCord11(freeverb, 0, mixer, 1);
AudioConnection          patchCord12(mixer, 0, dacs, 0);
AudioConnection          patchCord13(mixer, 0, dacs, 1);

#include "USBHost_t36.h"
USBHost             usbHost1;
USBHIDParser        usbHid1( usbHost1 );
JoystickController  stick( usbHost1 );
bool bouton[13];
float touch;
float smooTouch = 0.90;
float Xjoy, Yjoy, Zjoy;
float smooJoy = 0.20;
bool gamme = 1;
float penta[11] = {98.0, 110.0, 130.81, 146.83, 164.81, 196.0, 220.0, 261.63, 293.66, 329.63, 392.0};
byte mode = 7;

//#define DEBUG 1

void setup( ) {
#ifdef DEBUG
  delay(500);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
#endif
  AudioMemory(30);
  usbHost1.begin();

  noise.amplitude(1.0);
  shapeosc.amplitude(1);//(Zjoy / 255.0);
  lfo.begin(1.0, 4, WAVEFORM_SINE);
  //  lfo.frequency(20.0);
  //  lfo.amplitude(0.1);
  mixerfm.gain(0 , 0.0);
  mixerfm.gain(1 , 0.0);
  trisaw.begin(WAVEFORM_SAWTOOTH); /// type d'oscillateur
  trisaw.amplitude(0.5);
  trisaw.frequency(220.0);
  trisaw.frequencyModulation(2); //1 -12 octaves
  //trisaw.phaseModulation(180.0); // full phase modulation
  mixerfilter.gain(0 , 0.0);
  mixerfilter.gain(1 , 0.0);
  filter.frequency(4444);
  filter.resonance(2.7);   //0.7 à 5.0 résonnance
  filter.octaveControl(2.0);
  freeverb.roomsize(0.5); // 0.0 à 1.0
  freeverb.damping(0.1); // 0.0 à 1.0
  mixer.gain(0 , 0.5);
  mixer.gain(1 , 0.2);

  delay(400);
}

void loop() {


  touch = (1.0 - smooTouch) * touch + smooTouch * touchRead(30);
  usbHost1.Task();
  Xjoy = (1.0 - smooJoy) * Xjoy + smooJoy * stick.getAxis( 0 );
  Yjoy = (1.0 - smooJoy) * Yjoy + smooJoy * stick.getAxis( 1 );
  Zjoy = (1.0 - smooJoy) * Zjoy + smooJoy * stick.getAxis( 5 );
  //int Cross = stick.getAxis( 9 );
  uint32_t buttons = stick.getButtons();
  for (int i = 1; i < 13; i++) {
    bouton[i] = (buttons >> (i - 1)) & 1;
  }
  /////////////////////////////////////////////FIN aquisition
  if (!gamme)trisaw.frequency((1023 - Xjoy) / 4.0 + 60.0);
  else {
    trisaw.frequency(penta[(int) (1023 - Xjoy) / 94]);
  }
  float cutoff = constrain(touch - 1800.0, 0, 5555.0);
  cutoff = sq(cutoff) / 300;

  filter.frequency(cutoff);
  //shapeosc.amplitude(1.0); //(Zjoy / 255.0);
  if (mode == 7) {
    if (Yjoy >= 511) mixerfilter.gain(1, (Yjoy - 511.0) / 512.0);
    else {
      mixerfm.gain(1, (511.0 - Yjoy) / 2000.0);
    }
  }
  if (mode == 8) {
    if (Yjoy >= 511) mixerfilter.gain(0, (Yjoy - 511.0) / 512.0);
    else {
      mixerfm.gain(0, (511.0 - Yjoy) / 512.0);
    }
  }
 
  lfo.frequency(((1024 - Xjoy) / 4.0 + 60.0) / 4);
  //shapeosc.amplitude((Zjoy) / 1024.0); //(Zjoy / 255.0);
  if (bouton[12]) gamme = 0;
  if (bouton[11]) gamme = 1;
  if (bouton[7]) mode = 7 ;
  if (bouton[8])  mode =  8;
  if (bouton[9])  mode = 9 ;
  if (bouton[10])  mode = 10 ;

  if (bouton[2]) ;
  ///////// fin à tester
  delay(5);
#ifdef DEBUG
  Serial.println(touch);
  //Serial.print( buttons, BIN);
  Serial.println( Xjoy);
  Serial.println(cutoff);
#endif
}
