#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      pink1;          //xy=63,66
AudioSynthNoisePink      pink3;          //xy=63,220
AudioSynthNoisePink      pink2;          //xy=65,147
AudioSynthNoisePink      pink6;          //xy=65,398
AudioSynthNoisePink      pink5;          //xy=67,343
AudioSynthNoisePink      pink7;          //xy=67,471
AudioSynthNoisePink      pink4;          //xy=68,286
AudioSynthWaveformModulated waveformMod6;   //xy=221,405
AudioSynthWaveformModulated waveformMod7;   //xy=223,478
AudioSynthWaveformModulated waveformMod5;   //xy=227,350
AudioSynthWaveformModulated waveformMod1;   //xy=230,70
AudioSynthWaveformModulated waveformMod2;   //xy=230,148
AudioSynthWaveformModulated waveformMod3;   //xy=233,224
AudioSynthWaveformModulated waveformMod4;   //xy=233,293
AudioFilterStateVariable filter3;        //xy=377,230
AudioFilterStateVariable filter2;        //xy=382,153
AudioFilterStateVariable filter1;        //xy=385,77
AudioFilterStateVariable filter4;        //xy=411,291
AudioFilterStateVariable filter7;        //xy=417,482
AudioFilterStateVariable filter6;        //xy=420,410
AudioFilterStateVariable filter5;        //xy=422,351
AudioMixer4              mixer1;         //xy=538,127
AudioMixer4              mixer2;         //xy=636,219
AudioEffectFreeverb      freeverb;      //xy=654,289
AudioOutputAnalogStereo  dacs;           //xy=693,353
AudioConnection          patchCord1(pink1, 0, waveformMod1, 0);
AudioConnection          patchCord2(pink3, 0, waveformMod3, 0);
AudioConnection          patchCord3(pink2, 0, waveformMod2, 0);
AudioConnection          patchCord4(pink6, 0, waveformMod6, 0);
AudioConnection          patchCord5(pink5, 0, waveformMod5, 0);
AudioConnection          patchCord6(pink7, 0, waveformMod7, 0);
AudioConnection          patchCord7(pink4, 0, waveformMod4, 0);
AudioConnection          patchCord8(waveformMod6, 0, filter6, 0);
AudioConnection          patchCord9(waveformMod7, 0, filter7, 0);
AudioConnection          patchCord10(waveformMod5, 0, filter5, 0);
AudioConnection          patchCord11(waveformMod1, 0, filter1, 0);
AudioConnection          patchCord12(waveformMod2, 0, filter2, 0);
AudioConnection          patchCord13(waveformMod3, 0, filter3, 0);
AudioConnection          patchCord14(waveformMod4, 0, filter4, 0);
AudioConnection          patchCord15(filter3, 0, mixer1, 2);
AudioConnection          patchCord16(filter2, 0, mixer1, 1);
AudioConnection          patchCord17(filter1, 0, mixer1, 0);
AudioConnection          patchCord18(filter4, 0, mixer1, 3);
AudioConnection          patchCord19(filter7, 0, mixer2, 3);
AudioConnection          patchCord20(filter6, 0, mixer2, 2);
AudioConnection          patchCord21(filter5, 0, mixer2, 1);
AudioConnection          patchCord22(mixer1, 0, mixer2, 0);
AudioConnection          patchCord23(mixer2, freeverb);
AudioConnection          patchCord24(freeverb, 0, dacs, 0);
AudioConnection          patchCord25(freeverb, 0, dacs, 1);
// GUItool: end automatically generated code
float pinkLevel = 0.01;
float sawLevel = 0.5;
float sawFreq[7] = {110, 178, 288, 466, 754, 1220, 1973.62};
byte pinTouch[7] = {18, 23, 17, 22, 16, 19, 15};
int touchAver[7] = {0};
float touch[7];
float smooth = 0.5;
float freqCut[7];
float res = 1.8;

//#define DEBUG


void setup() {
#ifdef DEBUG
  delay(500);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
#endif
  AudioMemory(30);
  pink1.amplitude(pinkLevel); pink2.amplitude(pinkLevel); pink3.amplitude(pinkLevel); pink4.amplitude(pinkLevel); pink5.amplitude(pinkLevel); pink6.amplitude(pinkLevel); pink7.amplitude(pinkLevel);
  waveformMod1.begin(WAVEFORM_SAWTOOTH); waveformMod2.begin(WAVEFORM_SAWTOOTH); waveformMod3.begin(WAVEFORM_SAWTOOTH); waveformMod4.begin(WAVEFORM_SAWTOOTH); waveformMod5.begin(WAVEFORM_SAWTOOTH); waveformMod6.begin(WAVEFORM_SAWTOOTH); waveformMod7.begin(WAVEFORM_SAWTOOTH);
  waveformMod1.amplitude(sawLevel); waveformMod2.amplitude(sawLevel); waveformMod3.amplitude(sawLevel); waveformMod4.amplitude(sawLevel); waveformMod5.amplitude(sawLevel); waveformMod6.amplitude(sawLevel); waveformMod7.amplitude(sawLevel);
  waveformMod1.frequency(sawFreq[0]); waveformMod2.frequency(sawFreq[1]); waveformMod3.frequency(sawFreq[2]); waveformMod4.frequency(sawFreq[3]); waveformMod5.frequency(sawFreq[4]); waveformMod6.frequency(sawFreq[5]); waveformMod7.frequency(sawFreq[6]);
  filter1.resonance(res);filter2.resonance(res);filter3.resonance(res);filter4.resonance(res);filter5.resonance(res);filter6.resonance(res);filter7.resonance(res);
  //filter1.frequency(0);filter2.frequency(0);filter3.frequency(0);filter4.frequency(0);filter5.frequency(0);filter6.frequency(0);filter7.frequency(0);
  freeverb.roomsize(0.01);
  freeverb.damping(0.01);
  for (int h = 0; h < 100; h++) {
    for (int i = 0; i < 7; i++) {
      touchAver[i] = touchAver[i] + touchRead(pinTouch[i]);
    }
  }
  for (int i = 0; i < 7; i++) {
    touchAver[i] = touchAver[i] / 100;
  }

}

void loop() {
#ifdef DEBUG
  for (int i = 0; i < 7; i++) {
    Serial.print(touchRead(pinTouch[i]) - touchAver[i]);
    Serial.print("\t");
  }
Serial.println();
#endif
  for (int i = 0; i < 7; i++) {
    touch[i] = smooth * touch[i] + (1.0 - smooth) * (touchRead(pinTouch[i]) - touchAver[i]);
    freqCut[i] = (sq(touch[i])-10000)/100;
    freqCut[i]  = constrain(freqCut[i],0,20000);
  }
  filter1.frequency( freqCut[0]); filter2.frequency(freqCut[1]); filter3.frequency(freqCut[2]); filter4.frequency(freqCut[3]); filter5.frequency(freqCut[4]); filter6.frequency(freqCut[5]); filter7.frequency(freqCut[6]);
  delay(20);
}
