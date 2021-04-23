#define bounceTime 10
#include <Bounce.h>
Bounce bouncer0 = Bounce( 0, bounceTime );
Bounce bouncer1 = Bounce( 1, bounceTime );
Bounce bouncer2 = Bounce( 2, bounceTime );
Bounce bouncer3 = Bounce( 3, bounceTime );
Bounce bouncer4 = Bounce( 4, bounceTime );
Bounce bouncer5 = Bounce( 5, bounceTime );
Bounce bouncer6 = Bounce( 6, bounceTime );
Bounce bouncer7 = Bounce( 7, bounceTime );
Bounce bouncer8 = Bounce( 8, bounceTime );
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#define LED 13
// GUItool: begin automatically generated code
AudioPlaySdRaw           playSdRaw0;     //xy=132,76
AudioPlaySdRaw           playSdRaw1;     //xy=169,107
AudioPlaySdRaw           playSdRaw2;     //xy=198,137
AudioPlaySdRaw           playSdRaw3;     //xy=224,168
AudioPlaySdRaw           playSdRaw4;     //xy=249,200
AudioPlaySdRaw           playSdRaw5;     //xy=277,236
AudioPlaySdRaw           playSdRaw6;     //xy=300,269
AudioPlaySdRaw           playSdRaw7;     //xy=325,302
AudioPlaySdRaw           playSdRaw8;     //xy=358,334
AudioMixer4              mixer1;         //xy=465,121
AudioMixer4              mixer2;         //xy=513,212
AudioMixer4              mixer3;         //xy=672,269
AudioEffectGranular      granular;      //xy=835,240
AudioEffectBitcrusher    bitcrusher;    //xy=849,331
AudioOutputAnalogStereo  dacs;           //xy=1040,259
AudioConnection          patchCord1(playSdRaw0, 0, mixer1, 0);
AudioConnection          patchCord2(playSdRaw1, 0, mixer1, 1);
AudioConnection          patchCord3(playSdRaw2, 0, mixer1, 2);
AudioConnection          patchCord4(playSdRaw3, 0, mixer1, 3);
AudioConnection          patchCord5(playSdRaw4, 0, mixer2, 0);
AudioConnection          patchCord6(playSdRaw5, 0, mixer2, 1);
AudioConnection          patchCord7(playSdRaw6, 0, mixer2, 2);
AudioConnection          patchCord8(playSdRaw7, 0, mixer2, 3);
AudioConnection          patchCord9(playSdRaw8, 0, mixer3, 2);
AudioConnection          patchCord10(mixer1, 0, mixer3, 0);
AudioConnection          patchCord11(mixer2, 0, mixer3, 1);
AudioConnection          patchCord12(mixer3, granular);
AudioConnection          patchCord13(granular, bitcrusher);
AudioConnection          patchCord14(bitcrusher, 0, dacs, 0);
AudioConnection          patchCord15(bitcrusher, 0, dacs, 1);
// GUItool: end automatically generated code

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used
uint8_t pinBouton[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
float ratio;
int knobA9;
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
//#define DEBUG 1

void setup() {
#ifdef DEBUG
  delay(500);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
#endif
  AudioMemory(30);
  pinMode(13, OUTPUT);
  for (int i = 0; i < 9; i++) {
    pinMode(pinBouton[i], INPUT_PULLUP);
  }
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
  mixer3.gain(0, 0.7);
  mixer3.gain(1, 0.7);
  mixer3.gain(2, 0.7);
  mixer3.gain(3, 0.7);
  granular.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  bitcrusher.bits(16);
  bitcrusher.sampleRate(8888);
  granular.beginPitchShift(20);
}
void loop() {

  // ++ deux potentiomètres => bitcrusher / stutter /
  //  float knobA8 = (float)analogRead(A8) / 1023.0;
  //  float knobA9 = (float)analogRead(A9) / 1023.0;
  //bitcrusher.bits(12);
  int bitres = 2 + sq((float)analogRead(A8)) / 100000.0;
  bitcrusher.bits(bitres);
  bitcrusher.sampleRate(50+sq((float)analogRead(A8))/ 24.0);
  int knobA9 = analogRead(A9);
  if (knobA9 <= 512) {
    ratio = map((float)knobA9, 0,512,0.25,1.0);
  }
    if (knobA9 > 512) {
    ratio = map((float)knobA9, 512,1023,1.0,4.0);
  }
  if (ratio < 1.05 && ratio > 0.95) granular.stop();
  else {
    granular.beginPitchShift(20); granular.setSpeed(ratio);
  }

  bouncer0.update ( );
  bouncer1.update ( );
  bouncer2.update ( );
  bouncer3.update ( );
  bouncer4.update ( );
  bouncer5.update ( );
  bouncer6.update ( );
  bouncer7.update ( );
  bouncer8.update ( );
  if ( bouncer0.fallingEdge()) {
    playSdRaw0.play("s0.raw");
  }
  if ( bouncer1.fallingEdge()) {
    playSdRaw1.play("s1.raw");
  }
  if ( bouncer2.fallingEdge()) {
    playSdRaw2.play("s2.raw");
  }
  if ( bouncer3.fallingEdge()) {
    playSdRaw3.play("s3.raw");
  }
  if ( bouncer4.fallingEdge()) {
    playSdRaw4.play("s4.raw");
  }
  if ( bouncer5.fallingEdge()) {
    playSdRaw5.play("s5.raw");
  }
  if ( bouncer6.fallingEdge()) {
    playSdRaw6.play("s6.raw");
  }
  if ( bouncer7.fallingEdge()) {
    playSdRaw7.play("s7.raw");
  }
  if ( bouncer8.fallingEdge()) {
    playSdRaw8.play("s8.raw");
  }
#ifdef DEBUG
  Serial.println(bitres);
  //Serial.print( buttons, BIN);
//Serial.println(analogRead(A8));
  //  Serial.println(cutoff);
#endif
}
