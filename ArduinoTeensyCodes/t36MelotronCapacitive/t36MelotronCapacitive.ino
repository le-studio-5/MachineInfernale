#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdRaw           playSdRaw0;     //xy=69,20
AudioPlaySdRaw           playSdRaw1;     //xy=69,78
AudioPlaySdRaw           playSdRaw2;     //xy=69,150
AudioPlaySdRaw           playSdRaw3;     //xy=69,218
AudioPlaySdRaw           playSdRaw4;     //xy=69,287
AudioPlaySdRaw           playSdRaw5;     //xy=69,356
AudioPlaySdRaw           playSdRaw6;     //xy=69,424
AudioFilterStateVariable filter0;        //xy=237,27.5
AudioFilterStateVariable filter2;        //xy=243,154
AudioFilterStateVariable filter6;        //xy=242,426
AudioFilterStateVariable filter4;        //xy=243,289
AudioFilterStateVariable filter1;        //xy=244,87
AudioFilterStateVariable filter3;        //xy=245,218
AudioFilterStateVariable filter5;        //xy=245,359
AudioMixer4              mixer1;         //xy=399,103
AudioMixer4              mixer2;         //xy=480,201
AudioEffectGranular      granular;       //xy=614,202
AudioEffectBitcrusher    bitcrusher;     //xy=748,200
AudioOutputAnalogStereo  dacs;           //xy=885,198
AudioConnection          patchCord1(playSdRaw0, 0, filter0, 0);
AudioConnection          patchCord2(playSdRaw1, 0, filter1, 0);
AudioConnection          patchCord3(playSdRaw2, 0, filter2, 0);
AudioConnection          patchCord4(playSdRaw3, 0, filter3, 0);
AudioConnection          patchCord5(playSdRaw4, 0, filter4, 0);
AudioConnection          patchCord6(playSdRaw5, 0, filter5, 0);
AudioConnection          patchCord7(playSdRaw6, 0, filter6, 0);
AudioConnection          patchCord8(filter0, 0, mixer1, 0);
AudioConnection          patchCord9(filter2, 0, mixer1, 2);
AudioConnection          patchCord10(filter6, 0, mixer2, 2);
AudioConnection          patchCord11(filter4, 0, mixer2, 0);
AudioConnection          patchCord12(filter1, 0, mixer1, 1);
AudioConnection          patchCord13(filter3, 0, mixer1, 3);
AudioConnection          patchCord14(filter5, 0, mixer2, 1);
AudioConnection          patchCord15(mixer1, 0, mixer2, 3);
AudioConnection          patchCord16(mixer2, granular);
AudioConnection          patchCord17(granular, bitcrusher);
AudioConnection          patchCord18(bitcrusher, 0, dacs, 0);
AudioConnection          patchCord19(bitcrusher, 0, dacs, 1);
// GUItool: end automatically generated code
AudioPlaySdRaw *sdRaw[7] = {
  &playSdRaw0,  &playSdRaw1, &playSdRaw2, &playSdRaw3, &playSdRaw4, &playSdRaw5, &playSdRaw6
};
AudioFilterStateVariable *filter[7] = {
  &filter0,  &filter1,  &filter2,  &filter3,  &filter4,  &filter5,  &filter6
};
// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used
//uint8_t pinBouton[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
float ratio;
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
float level = 0.25;
//float sawFreq[7] = {110, 178, 288, 466, 754, 1220, 1973.62};
byte pinTouch[11] = {15, 16, 17, 18, 19, 22, 23, 0, 1, 29, 30};
int touchAver[7] = {0};
float touch[7];
float smooth = 0.5;
float res = 1.8;
char sample[7][7] = { "s0.raw", "s1.raw", "s2.raw", "s3.raw", "s4.raw", "s5.raw", "s6.raw",};// 10 is the length of the longest string + 1 ( for the '\0' at the end )

//#define DEBUG 1

void setup() {
#ifdef DEBUG
  delay(500);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
#endif
  AudioMemory(60);
  pinMode(13, OUTPUT);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  while (!(SD.begin(SDCARD_CS_PIN))) {
    digitalWrite(13, LOW);
    delay (100);
    digitalWrite(13, HIGH);
    delay (100);
  }
  digitalWrite(13, HIGH);
  delay(100);
  mixer1.gain(0, level);
  mixer1.gain(1, level);
  mixer1.gain(2, level);
  mixer1.gain(3, level);
  mixer2.gain(0, level);
  mixer2.gain(1, level);
  mixer2.gain(2, level);
  mixer2.gain(3, 1.0);
  for (int i = 0; i < 7; i++) {
    filter[i]->resonance(res);
    filter[i]->frequency(500);
  }
  granular.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  bitcrusher.bits(16);
  bitcrusher.sampleRate(44000);
  //granular.beginPitchShift(20);
  for (int h = 0; h < 100; h++) {
    for (int i = 0; i < 7; i++) {
      touchAver[i] = touchAver[i] + touchRead(pinTouch[i]);
      delay(10);
    }
  }
  for (int i = 0; i < 7; i++) {
    touchAver[i] = touchAver[i] / 100;
  }

}
void loop() {

  // ++ deux potentiomètres => bitcrusher / stutter /
  //  float knobA8 = (float)analogRead(A8) / 1023.0;
  //  float knobA9 = (float)analogRead(A9) / 1023.0;
  //bitcrusher.bits(12);
  //  int bitres = 2 + sq((float)analogRead(A8)) / 100000.0;
  //  bitcrusher.bits(bitres);
  //  bitcrusher.sampleRate(50 + sq((float)analogRead(A8)) / 24.0);
  //  int knobA9 = analogRead(A9);
  //  if (knobA9 <= 512) {
  //    ratio = map((float)knobA9, 0, 512, 0.25, 1.0);
  //  }
  //  if (knobA9 > 512) {
  //    ratio = map((float)knobA9, 512, 1023, 1.0, 4.0);
  //  }
  //  if (ratio < 1.05 && ratio > 0.95) granular.stop();
  //  else {
  //    granular.beginPitchShift(20); granular.setSpeed(ratio);
  //  }
  for (int i = 0; i < 7; i++) {
    touch[i] = smooth * touch[i] + (1.0 - smooth) * (touchRead(pinTouch[i]) - touchAver[i]);
    float freqCut = (sq(touch[i]) - 10000) / 100;
    freqCut  = constrain(freqCut, 0, 20000);
    filter[i]->frequency(freqCut);
#ifdef DEBUG
    Serial.println(touch[i]);//Serial.print( buttons, BIN);//Serial.println(analogRead(A8));//  Serial.println(cutoff);
#endif
    if ( sdRaw[i]->isPlaying() == 0 && touch[i] > 100) {
      sdRaw[i]->play(sample[i]);
    }
else if (touch[i] < 90) {
      sdRaw[i]->stop();
    }
    delay(5);
  }
 
}
