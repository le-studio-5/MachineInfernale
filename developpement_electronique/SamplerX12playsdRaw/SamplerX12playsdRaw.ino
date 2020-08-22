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
Bounce bouncer9 = Bounce( 9, bounceTime );
Bounce bouncer10 = Bounce( 10, bounceTime );
Bounce bouncer11 = Bounce( 11, bounceTime );

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#define LED 13

// GUItool: begin automatically generated code
AudioPlaySdRaw           playSdRaw5;     //xy=127,175
AudioPlaySdRaw           playSdRaw6;     //xy=128,205
AudioPlaySdRaw           playSdRaw7;     //xy=128,231
AudioPlaySdRaw           playSdRaw4;     //xy=129,148
AudioPlaySdRaw           playSdRaw9;     //xy=129,305
AudioPlaySdRaw           playSdRaw10;    //xy=129,333
AudioPlaySdRaw           playSdRaw11;    //xy=129,360
AudioPlaySdRaw           playSdRaw8;     //xy=131,276
AudioPlaySdRaw           playSdRaw0;    //xy=135,20
AudioPlaySdRaw           playSdRaw1;     //xy=135,48
AudioPlaySdRaw           playSdRaw2;     //xy=135,81
AudioPlaySdRaw           playSdRaw3;     //xy=136,109
AudioMixer4              mixer1;         //xy=374,62
AudioMixer4              mixer2;         //xy=392,162
AudioMixer4              mixer3;         //xy=392,284
AudioMixer4              mixer4;         //xy=528,163
AudioOutputAnalogStereo  dacs2; //xy=666,163
AudioConnection          patchCord1(playSdRaw5, 0, mixer2, 1);
AudioConnection          patchCord2(playSdRaw6, 0, mixer2, 2);
AudioConnection          patchCord3(playSdRaw7, 0, mixer2, 3);
AudioConnection          patchCord4(playSdRaw4, 0, mixer2, 0);
AudioConnection          patchCord5(playSdRaw9, 0, mixer3, 1);
AudioConnection          patchCord6(playSdRaw10, 0, mixer3, 2);
AudioConnection          patchCord7(playSdRaw11, 0, mixer3, 3);
AudioConnection          patchCord8(playSdRaw8, 0, mixer3, 0);
AudioConnection          patchCord9(playSdRaw0, 0, mixer1, 0);
AudioConnection          patchCord10(playSdRaw1, 0, mixer1, 1);
AudioConnection          patchCord11(playSdRaw2, 0, mixer1, 2);
AudioConnection          patchCord12(playSdRaw3, 0, mixer1, 3);
AudioConnection          patchCord13(mixer1, 0, mixer4, 0);
AudioConnection          patchCord14(mixer2, 0, mixer4, 1);
AudioConnection          patchCord15(mixer3, 0, mixer4, 2);
AudioConnection          patchCord16(mixer4, 0, dacs2, 0);
AudioConnection          patchCord17(mixer4, 0, dacs2, 1);
// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used
uint8_t pinBouton[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
  //Serial.begin(9600);
  AudioMemory(30);
  pinMode(13, OUTPUT);
  for (int i = 0; i < 12; i++) {
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
  mixer4.gain(0, 0.7);
  mixer4.gain(1, 0.7);
  mixer4.gain(2, 0.7);
  mixer4.gain(3, 0.7);
}

void loop() {
  bouncer0.update ( );
  bouncer1.update ( );
  bouncer2.update ( );
  bouncer3.update ( );
  bouncer4.update ( );
  bouncer5.update ( );
  bouncer6.update ( );
  bouncer7.update ( );
  bouncer8.update ( );
  bouncer9.update ( );
  bouncer10.update ( );
  bouncer11.update ( );
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
  if ( bouncer9.fallingEdge()) {
    playSdRaw9.play("s9.raw");
  }
  if ( bouncer10.fallingEdge()) {
    playSdRaw10.play("s10.raw");
  }
  if ( bouncer11.fallingEdge()) {
    playSdRaw11.play("s11.raw");
  }
  delay(10);
}
