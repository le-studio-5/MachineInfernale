#define bounceTime 20
#include <FastLED.h>
CRGB leds[8];
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdRaw           playSdRaw0;     //xy=69,93
AudioPlaySdRaw           playSdRaw1;     //xy=106,124
AudioPlaySdRaw           playSdRaw2;     //xy=135,154
AudioPlaySdRaw           playSdRaw3;     //xy=161,185
AudioMixer4              mixer1;         //xy=402,138
AudioOutputAnalogStereo  dacs;           //xy=625,143
AudioConnection          patchCord1(playSdRaw0, 0, mixer1, 0);
AudioConnection          patchCord2(playSdRaw1, 0, mixer1, 1);
AudioConnection          patchCord3(playSdRaw2, 0, mixer1, 2);
AudioConnection          patchCord4(playSdRaw3, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, dacs, 0);
AudioConnection          patchCord6(mixer1, 0, dacs, 1);
// GUItool: end automatically generated code
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used
uint8_t pinStep[8] = {0, 1, 2, 3, 4, 5, 6, 7};
uint8_t pinLine[4] = {8, 9, 10, 11};
uint8_t Step = 0;
unsigned long previousMillis;
int tInt;

void setup() {
   FastLED.addLeds<WS2812B, 22, GRB>(leds, 8);
  AudioMemory(20);
  pinMode(13, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(pinStep[i], OUTPUT);
    digitalWrite(pinStep[i], HIGH);
  }
  digitalWrite(pinStep[0], LOW);
  for (int i = 0; i < 4; i++) {
    pinMode(pinLine[i], INPUT_PULLUP);

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
  mixer1.gain(0, 0.7);
  mixer1.gain(1, 0.7);
  mixer1.gain(2, 0.7);
  mixer1.gain(3, 0.7);
}
void loop() {
  tInt = map(analogRead(A9), 0, 1023, 64, 1000);
   if (millis() >= previousMillis + tInt*0.33) {
     for (int i = 0; i < 8; i++) {
      leds[i] = 0;
    }
     FastLED.show();
   }
  if (millis() >= previousMillis + tInt) {
    previousMillis = millis();
    if (!digitalRead(pinLine[0])) {
      playSdRaw0.play("s0.raw");
    }
    if (!digitalRead(pinLine[1])) {
      playSdRaw1.play("s1.raw");
    }
    if (!digitalRead(pinLine[2])) {
      playSdRaw2.play("s2.raw");
    }
    if (!digitalRead(pinLine[3]) ) {
      playSdRaw3.play("s3.raw");
    }
    for (int i = 0; i < 8; i++) {
      pinMode(pinStep[i], OUTPUT);
      digitalWrite(pinStep[i], HIGH);
      leds[i] = 0;
    }
    leds[7-Step] = 255;
     FastLED.show();
    Step = (Step + 1) % 8;
    digitalWrite(pinStep[Step], LOW);
  }
}
