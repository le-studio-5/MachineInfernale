#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
//#include <SD.h>
//#include <SerialFlash.h>

#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=178,261
AudioFilterStateVariable filter1;        //xy=302,379
AudioOutputAnalogStereo  dacs1;          //xy=581,302
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 0, dacs1, 0);
AudioConnection          patchCord3(filter1, 0, dacs1, 1);
// GUItool: end automatically generated code

//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

#include <Smoothed.h>
Smoothed <uint32_t> cs0av;
Smoothed <uint32_t> cs1av;
Smoothed <uint32_t> cs2av;
Smoothed <uint32_t> cs3av;
const int ledPin = 13;
uint32_t csc;
const byte nb_cs = 8;
byte out[nb_cs] = {0, 2, 25, 11, 8, 10, 24, 26};
byte in[nb_cs] = {1, 3, 26, 12, 9, 11, 25, 27};
int calib[nb_cs];
int i;
uint32_t cs[8];

void setup()
{
  //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  for (i = 0; i < nb_cs; i++) {
    pinMode(in[i], INPUT);
    pinMode(out[i], OUTPUT);
    digitalWrite(out[i], LOW);
  }
  cs0av.begin(SMOOTHED_AVERAGE, 10);
  cs1av.begin(SMOOTHED_AVERAGE, 10);
  cs2av.begin(SMOOTHED_AVERAGE, 10);
  cs3av.begin(SMOOTHED_AVERAGE, 10);
  delay(500);
  Serial.print("go2");
  AudioMemory(20);
  waveform1.begin(0.7, 444, WAVEFORM_SAWTOOTH);

  //biquad1.setLowpass(0, 1, 0.7);
  //biquad2.setLowpass(0, 1, 0.7);
  //biquad3.setLowpass(0, 1, 0.7);
  //biquad4.setLowpass(0, 1, 0.7);
filter1.resonance(0.9);
  calibration();
}
void calibration() {
  for (i = 0; i < nb_cs; i++) {
    calib[i] = 0;
  }
  for (int n = 0; n < 100; n++) {
    for (int m = 0; m < 2; m++) {
      capsens(m);
      calib[m] = calib[m] + cs[m];
    }
    delay(10);
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
  }
  for (i = 0; i < 2; i++) {
    calib[i] = calib[i] / 100;

  }
}
void capsens(int i) {
  csc = 0;
  noInterrupts();
  pinMode(in[i], INPUT);
  digitalWrite(out[i], HIGH);
  while (digitalReadFast(in[i]) == LOW) {
    csc = csc + 1;
  }
  interrupts();
  digitalWrite(out[i], LOW);
  pinMode(in[i], OUTPUT); digitalWrite(in[i], LOW);
  cs[i] = csc;
}
void loop()
{
  //long start = millis();
  //  for (i = 0; i < 8; i++) {
  //    capsens(i);
  //  }
  //Serial.print(millis() - start);
  // Serial.print("\t");
  capsens(0);
  capsens(1);
  //  capsens(2);
  //  capsens(3);

  cs0av.add(cs[0]);
  cs1av.add(cs[1]);
  //  cs2av.add(cs[2]);
  //  cs3av.add(cs[3]);

  Serial.print(cs0av.get());
  Serial.print("\t");
  Serial.print(cs1av.get());

  int F1 = 444 + (cs1av.get() - cs0av.get()) * 8;
  F1 =constrain(F1, 50, 5000);
  int FF = cs1av.get() + cs0av.get()-850;
  
  FF =constrain(FF, 3, 330);
  FF = sq(FF)/6;
  //  int F2 = cs1av.get() - calib[1] - 20;
  //  F2 = constrain(F2, 3, 250);
  //  F2 = sq(F2) / 6;
  //  int F3 = cs2av.get() - calib[2] - 20;
  //  F3 = constrain(F3, 3, 250);
  //  F3 = sq(F3) / 6;
  //
  //  int F4 = cs3av.get() - calib[3] - 20;
  //  F4 = constrain(F4, 3, 250);
  //  F4 = sq(F4) / 6;
  //AudioNoInterrupts();
  waveform1.frequency(F1);
  filter1.frequency(FF);
  
  //AudioInterrupts();
  //Serial.print(F1);
  //  Serial.print("\t");
  //  Serial.print(F1);
  //  Serial.print("\t");
  //  Serial.print(F2);
  //  Serial.print("\t");
  //  Serial.print(F3);
  //  Serial.print("\t");
  //  Serial.print(F4);
  //   for (i = 0; i < 8; i++) {
  //     Serial.print("\t");
  //  Serial.print(cs[i]);
  //  }
  Serial.println();
  delay(10);                             // arbitrary delay to limit data to serial port
}
