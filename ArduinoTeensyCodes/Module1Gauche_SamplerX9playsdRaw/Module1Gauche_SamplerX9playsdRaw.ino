#define bounceTime 20
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
AudioPlaySdRaw           playSdRaw0;     //xy=107,22
AudioPlaySdRaw           playSdRaw1;     //xy=144,53
AudioPlaySdRaw           playSdRaw2;     //xy=173,83
AudioPlaySdRaw           playSdRaw3;     //xy=199,114
AudioPlaySdRaw           playSdRaw4;     //xy=224,146
AudioPlaySdRaw           playSdRaw5;     //xy=252,182
AudioPlaySdRaw           playSdRaw6;     //xy=275,215
AudioPlaySdRaw           playSdRaw7;     //xy=300,248
AudioPlaySdRaw           playSdRaw8;     //xy=333,280
AudioMixer4              mixer1;         //xy=440,67
AudioMixer4              mixer2;         //xy=488,158
AudioMixer4              mixer3;         //xy=647,215
AudioOutputAnalogStereo  dacs;          //xy=825,247
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
AudioConnection          patchCord12(mixer3, 0, dacs, 0);
AudioConnection          patchCord13(mixer3, 0, dacs, 1);
// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used
uint8_t pinBouton[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

void setup() {
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
}
void loop() {
  // ++ deux potentiomètres => bitcrusher / stutter / 
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
}
