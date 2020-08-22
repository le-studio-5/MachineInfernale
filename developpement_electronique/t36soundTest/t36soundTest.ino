#define bounceTime 20
#include <Bounce.h>
Bounce bouncer1 = Bounce( 1, bounceTime );
Bounce bouncer2 = Bounce( 2, bounceTime );
Bounce bouncer3 = Bounce( 3, bounceTime );
Bounce bouncer4 = Bounce( 4, bounceTime );
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#define LED 13
// GUItool: begin automatically generated code
// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=423,183
AudioOutputAnalogStereo  dacs1;          //xy=581,302
AudioConnection          patchCord1(sine1, 0, dacs1, 0);
AudioConnection          patchCord2(sine1, 0, dacs1, 1);
// GUItool: end automatically generated code
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
//#define SDCARD_CS_PIN    10
//#define SDCARD_MOSI_PIN  7
//#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13
int freq=110;

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  pinMode(13, OUTPUT);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
//  SPI.setMOSI(SDCARD_MOSI_PIN);
//  SPI.setSCK(SDCARD_SCK_PIN);
//  while (!(SD.begin(SDCARD_CS_PIN))) {
//    digitalWrite(13, LOW);
//    delay (100);
//    digitalWrite(13, HIGH);
//    delay (100);
//  }
  digitalWrite(13, HIGH);
  delay(100);
  sine1.amplitude(1.0);

sine1.frequency(freq);
}

void loop() {
  bouncer1.update ( );
  bouncer2.update ( );
  bouncer3.update ( );
  bouncer4.update ( );
//  sine1.amplitude(0.0);
//  delay(120);
  sine1.amplitude(1.0);
  delay(200);
  freq=3*freq/2;
  if(freq>3000)freq=110;
  sine1.frequency(freq);
//  if ( bouncer1.fallingEdge()) {
//    playSdRaw1.play("s1.raw");
//  }
//  if ( bouncer2.fallingEdge()) {
//    playSdRaw2.play("s2.raw");
//  }
//  if ( bouncer3.fallingEdge()) {
//    Serial.println("Start playing");
//    playSdRaw3.play("s3.raw");
//  }
//  if ( bouncer4.fallingEdge()) {
//    playSdRaw4.play("s4.raw");
//  }
}
