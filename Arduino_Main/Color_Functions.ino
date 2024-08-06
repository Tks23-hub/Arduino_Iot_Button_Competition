
void SettingUpLeds() {
  pinMode(pinLed_R, OUTPUT);
  pinMode(pinLed_G, OUTPUT);
  pinMode(pinLed_B, OUTPUT);
}

void TurnOnAndOFFTurquoise() {
  TurnOnTurquoise();
  delay(1000);
  TurnOffLED();
}

void TurnOnAndOFFBrown() {
  TurnOnBrown();
  delay(1000);
  TurnOffLED();
}

void TurnOnTurquoise() {
  LightLed(0x40E0D0); 
}

void TurnOnBrown() {
  LightLed(0xA52A2A); 
}

void TurnOffLED() {
  LightLed(0x000000);
}

void LightLed(long HexaColor) {
  int red = (HexaColor >> 16) & 0xFF;
  int green = (HexaColor >> 8) & 0xFF;
  int blue = HexaColor & 0xFF;

  analogWrite(pinLed_R, red);
  analogWrite(pinLed_G, green);
  analogWrite(pinLed_B, blue);
}
