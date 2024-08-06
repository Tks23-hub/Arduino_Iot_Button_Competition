#define BtnPin D1
#define pinLed_R D5
#define pinLed_G D6
#define pinLed_B D7
#define performanceModePin D2

int lastVal;
unsigned long pressStartTime;
unsigned long pressDuration;
unsigned long LastPressTime;
unsigned long lastPressDuration = 0;
unsigned long pressTimes[10]; // for the last 10 presses
int PressTimesTracker = 0; // so we don’t go out of the array borders
unsigned long shortestPress = 0xFFF; //  a high value
int cnt = 0;
int wifiCnt=0;


void setup() {
  Serial.begin(9600);
  pinMode(BtnPin, INPUT_PULLUP);
  pinMode(performanceModePin, INPUT_PULLUP);
  LastPressTime = millis();
  lastVal = digitalRead(BtnPin);
  SettingUpLeds();
  wifiClient_Setup(); 
  SendData(shortestPress);
   
}


void loop() {
  // We cant switch mode in the setup because then we have to rerun the code and the 
  // btn press array will be empty so we do it in the loop and we make sure its not an
  // endless loop 
if (digitalRead(performanceModePin) == LOW && wifiCnt==0 ) {
        wifiSetup();
        wifiCnt++;
   }
   else if (digitalRead(performanceModePin) == HIGH && wifiCnt>0){
    wifiClient_Setup(); 
    wifiCnt=0;
   }

  int val = digitalRead(BtnPin);
  if (val == LOW && lastVal == HIGH && (millis() - LastPressTime > 50)) {
    pressStartTime = millis();
    LastPressTime = millis();
  } else if (val == HIGH && lastVal == LOW && (millis() - LastPressTime > 50)) {
    pressDuration = millis() - pressStartTime;
    pressTimes[PressTimesTracker] = pressDuration;
    PressTimesTracker = (PressTimesTracker + 1) % 10; // so we don't get out of the array borders
    lastPressDuration = pressDuration;
    cnt++;

      unsigned long serverShortestPress = GetData();
      Serial.println(serverShortestPress);
    if (serverShortestPress == 0) { // If the server had no data 
      SendData(pressDuration);
      shortestPress = pressDuration;
      TurnOnAndOFFTurquoise();
    } else {
      if (pressDuration < serverShortestPress) {
        shortestPress = pressDuration;
        SendData(shortestPress); 
        TurnOnAndOFFTurquoise();
      } else {
        TurnOnAndOFFBrown();
      }
    }
  }
  lastVal = val;
  wifi_loop();
}