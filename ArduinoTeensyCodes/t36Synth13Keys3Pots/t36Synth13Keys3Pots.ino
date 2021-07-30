#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      pink11;         //xy=57,707
AudioSynthNoisePink      pink1;          //xy=63,66
AudioSynthNoisePink      pink3;          //xy=63,220
AudioSynthNoisePink      pink10;         //xy=62,655
AudioSynthNoisePink      pink13;         //xy=62,799
AudioSynthNoisePink      pink2;          //xy=65,147
AudioSynthNoisePink      pink6;          //xy=65,398
AudioSynthNoisePink      pink12;         //xy=64,757
AudioSynthNoisePink      pink8;          //xy=66,544
AudioSynthNoisePink      pink5;          //xy=67,343
AudioSynthNoisePink      pink9;          //xy=66,604
AudioSynthNoisePink      pink7;          //xy=67,471
AudioSynthNoisePink      pink4;          //xy=68,286
AudioSynthWaveformModulated waveformMod6;   //xy=221,405
AudioSynthWaveformModulated waveformMod7;   //xy=223,478
AudioSynthWaveformModulated waveformMod5;   //xy=227,350
AudioSynthWaveformModulated waveformMod1;   //xy=230,70
AudioSynthWaveformModulated waveformMod2;   //xy=230,148
AudioSynthWaveformModulated waveformMod3;   //xy=233,224
AudioSynthWaveformModulated waveformMod4;   //xy=233,293
AudioSynthWaveformModulated waveformMod8;   //xy=236,546
AudioSynthWaveformModulated waveformMod9;   //xy=238,607
AudioSynthWaveformModulated waveformMod13;  //xy=242,810
AudioSynthWaveformModulated waveformMod12;  //xy=243,763
AudioSynthWaveformModulated waveformMod10;  //xy=247,658
AudioSynthWaveformModulated waveformMod11;  //xy=247,709
AudioEffectEnvelope      envelope2;      //xy=401,144
AudioEffectEnvelope      envelope4;      //xy=403,293
AudioEffectEnvelope      envelope7;      //xy=405,485
AudioEffectEnvelope      envelope1;      //xy=409,83
AudioEffectEnvelope      envelope3;      //xy=410,214
AudioEffectEnvelope      envelope6;      //xy=412,406
AudioEffectEnvelope      envelope8;      //xy=413,548
AudioEffectEnvelope      envelope9;      //xy=413,602
AudioEffectEnvelope      envelope5;      //xy=423,352
AudioEffectEnvelope      envelope12;     //xy=423,761
AudioEffectEnvelope      envelope10;     //xy=426,650
AudioEffectEnvelope      envelope13;     //xy=427,806
AudioEffectEnvelope      envelope11;     //xy=428,705
AudioMixer4              mixer1;         //xy=568,184
AudioMixer4              mixer2;         //xy=606,424
AudioMixer4              mixer3;         //xy=620,662
AudioSynthWaveformSine   sine1;          //xy=771,402
AudioMixer4              mixer4;         //xy=784,317
AudioFilterStateVariable filter1;        //xy=919,404
AudioOutputAnalogStereo  dacs;           //xy=942,305
AudioConnection          patchCord1(pink11, 0, waveformMod11, 0);
AudioConnection          patchCord2(pink1, 0, waveformMod1, 0);
AudioConnection          patchCord3(pink3, 0, waveformMod3, 0);
AudioConnection          patchCord4(pink10, 0, waveformMod10, 0);
AudioConnection          patchCord5(pink13, 0, waveformMod13, 0);
AudioConnection          patchCord6(pink2, 0, waveformMod2, 0);
AudioConnection          patchCord7(pink6, 0, waveformMod6, 0);
AudioConnection          patchCord8(pink12, 0, waveformMod12, 0);
AudioConnection          patchCord9(pink8, 0, waveformMod8, 0);
AudioConnection          patchCord10(pink5, 0, waveformMod5, 0);
AudioConnection          patchCord11(pink9, 0, waveformMod9, 0);
AudioConnection          patchCord12(pink7, 0, waveformMod7, 0);
AudioConnection          patchCord13(pink4, 0, waveformMod4, 0);
AudioConnection          patchCord14(waveformMod6, envelope6);
AudioConnection          patchCord15(waveformMod7, envelope7);
AudioConnection          patchCord16(waveformMod5, envelope5);
AudioConnection          patchCord17(waveformMod1, envelope1);
AudioConnection          patchCord18(waveformMod2, envelope2);
AudioConnection          patchCord19(waveformMod3, envelope3);
AudioConnection          patchCord20(waveformMod4, envelope4);
AudioConnection          patchCord21(waveformMod8, envelope8);
AudioConnection          patchCord22(waveformMod9, envelope9);
AudioConnection          patchCord23(waveformMod13, envelope13);
AudioConnection          patchCord24(waveformMod12, envelope12);
AudioConnection          patchCord25(waveformMod10, envelope10);
AudioConnection          patchCord26(waveformMod11, envelope11);
AudioConnection          patchCord27(envelope2, 0, mixer1, 1);
AudioConnection          patchCord28(envelope4, 0, mixer1, 3);
AudioConnection          patchCord29(envelope7, 0, mixer2, 2);
AudioConnection          patchCord30(envelope1, 0, mixer1, 0);
AudioConnection          patchCord31(envelope3, 0, mixer1, 2);
AudioConnection          patchCord32(envelope6, 0, mixer2, 1);
AudioConnection          patchCord33(envelope8, 0, mixer2, 3);
AudioConnection          patchCord34(envelope9, 0, mixer3, 0);
AudioConnection          patchCord35(envelope5, 0, mixer2, 0);
AudioConnection          patchCord36(envelope12, 0, mixer3, 3);
AudioConnection          patchCord37(envelope10, 0, mixer3, 1);
AudioConnection          patchCord38(envelope13, 0, mixer4, 3);
AudioConnection          patchCord39(envelope11, 0, mixer3, 2);
AudioConnection          patchCord40(mixer1, 0, mixer4, 0);
AudioConnection          patchCord41(mixer2, 0, mixer4, 1);
AudioConnection          patchCord42(mixer3, 0, mixer4, 2);
AudioConnection          patchCord43(sine1, 0, filter1, 1);
AudioConnection          patchCord44(mixer4, 0, filter1, 0);
AudioConnection          patchCord45(filter1, 0, dacs, 0);
AudioConnection          patchCord46(filter1, 0, dacs, 1);
// GUItool: end automatically generated code
AudioSynthNoisePink *pink[13] = {
  &pink1, &pink2, &pink3, &pink4, &pink5, &pink6, &pink7, &pink8, &pink9, &pink10, &pink11, &pink12, &pink13
};
AudioSynthWaveformModulated *osc[13] = {
  &waveformMod1, &waveformMod2, &waveformMod3, &waveformMod4, &waveformMod5, &waveformMod6, &waveformMod7, &waveformMod8, &waveformMod9, &waveformMod10, &waveformMod11, &waveformMod12, &waveformMod13
};
AudioEffectEnvelope *env[13] = {
  &envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7, &envelope8, &envelope9, &envelope10, &envelope11, &envelope12, &envelope13
};

#include <Bounce.h>
int debT = 5;
Bounce b0 = Bounce(0, debT); Bounce b1 = Bounce(1, debT); Bounce b2 = Bounce(2, debT); Bounce b3 = Bounce(3, debT); Bounce b4 = Bounce(4, debT); Bounce b5 = Bounce(5, debT);
Bounce b6 = Bounce(6, debT); Bounce b7 = Bounce(7, debT); Bounce b8 = Bounce(8, debT); Bounce b9 = Bounce(9, debT); Bounce b10 = Bounce(10, debT); Bounce b11 = Bounce(11, debT); Bounce b12 = Bounce(12, debT);
Bounce *b[13] = {
  &b0, &b1,  &b2,  &b3,  &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12
};

float sawFreq[13] = {261.6256, 277.1826, 293.6648, 311.1270, 329.6276, 349.2282 , 369.9944, 391.9954, 415.3047, 440.0000, 466.1638, 493.8833, 523.2511};
//byte pinKey[13] = {18, 23, 17, 22, 16, 19, 15};
float pinkLevel = 0.01;
float sawLevel = 0.25;
float smooth = 0.5;
float freqCut = 200;
float res = 2.8;

//#define DEBUG


void setup() {
#ifdef DEBUG
  delay(500);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
#endif
  analogReadRes(12);
  for (int i = 0; i < 13; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  AudioMemory(30);
  pink1.amplitude(pinkLevel); pink2.amplitude(pinkLevel); pink3.amplitude(pinkLevel); pink4.amplitude(pinkLevel); pink5.amplitude(pinkLevel); pink6.amplitude(pinkLevel); pink7.amplitude(pinkLevel);
  //waveformMod1. waveformMod2.begin(WAVEFORM_SAWTOOTH); waveformMod3.begin(WAVEFORM_SAWTOOTH); waveformMod4.begin(WAVEFORM_SAWTOOTH); waveformMod5.begin(WAVEFORM_SAWTOOTH); waveformMod6.begin(WAVEFORM_SAWTOOTH); waveformMod7.begin(WAVEFORM_SAWTOOTH);
  // waveformMod1.amplitude(sawLevel); waveformMod2.amplitude(sawLevel); waveformMod3.amplitude(sawLevel); waveformMod4.amplitude(sawLevel); waveformMod5.amplitude(sawLevel); waveformMod6.amplitude(sawLevel); waveformMod7.amplitude(sawLevel);
  //waveformMod1.frequency(sawFreq[0]); waveformMod2.frequency(sawFreq[1]); waveformMod3.frequency(sawFreq[2]); waveformMod4.frequency(sawFreq[3]); waveformMod5.frequency(sawFreq[4]); waveformMod6.frequency(sawFreq[5]); waveformMod7.frequency(sawFreq[6]);
  //waveformMod8.frequency(sawFreq[7]); waveformMod9.frequency(sawFreq[8]); waveformMod10.frequency(sawFreq[9]); waveformMod11.frequency(sawFreq[10]); waveformMod12.frequency(sawFreq[11]); waveformMod13.frequency(sawFreq[12]);

  for (int i = 0; i < 13; i++) {
    osc[i]->begin(WAVEFORM_SAWTOOTH);
    osc[i]->amplitude(sawLevel);
    osc[i]->frequency(sawFreq[i]);
    env[i]->attack(119.2);
    env[i]->hold(2.1);
    env[i]->decay(31.4);
    env[i]->sustain(0.6);
    env[i]->release(384.5);

  }
  filter1.resonance(res);
  filter1.frequency(freqCut);
}

void loop() {
#ifdef DEBUG

  Serial.println();
#endif
  freqCut = sq(analogRead(A5)) / 4096.0;
  filter1.frequency(freqCut);
  float pinkLvl = sq(analogRead(A7) / 4096.0);
  float sineLvl = constrain(50*sq(analogRead(A6) / 4096.0),0.0 ,1.0);
  sine1.amplitude(sineLvl);
  float sineFreq = sq(analogRead(A6) / 4096.0)*100.0;
  sine1.frequency(sineFreq);
  for (int i = 0; i < 13; i++) {
    b[i]->update();
    if (b[i]->fallingEdge()) {
      env[i]->noteOn();
    }
    if (b[i]->risingEdge()) {
      env[i]->noteOff();
    }
    pink[i]->amplitude(pinkLvl);
  }


  //delay(20);
}
