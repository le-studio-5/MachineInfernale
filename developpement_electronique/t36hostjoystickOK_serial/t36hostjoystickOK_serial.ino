// Joystick Logitec extreme3Dpro to teensy3.6 to sérial

#include "USBHost_t36.h"

USBHost             usbHost1;
USBHIDParser        usbHid1( usbHost1 );
JoystickController  stick( usbHost1 );

void setup( ) {
  usbHost1.begin();
  Serial.begin( 115200 );
}

void loop() {
  usbHost1.Task();

  int Xjoy = stick.getAxis( 0 );
  int Yjoy = stick.getAxis( 1 );
  int Zjoy = stick.getAxis( 5 );
  int Cross = stick.getAxis( 9 );
  uint32_t buttons = stick.getButtons();
  int Ajoy = stick.getAxis( 17 );
  int Bjoy = stick.getAxis( 18 );
  int Cjoy = stick.getAxis( 19 );
  Serial.print(Xjoy);
  Serial.print("\t");
  Serial.print(Yjoy);
  Serial.print("\t");
  Serial.print(Zjoy);
  Serial.print("\t");
  Serial.print(Cross);
  Serial.print("\t");
  Serial.print(buttons + 0x1000, BIN);
  //  Serial.print("\t");
  //  Serial.print(Ajoy);
  //  Serial.print("\t");
  //  Serial.print(Bjoy);
  //  Serial.print("\t");
  //  Serial.print(Cjoy);
  Serial.println();
}
