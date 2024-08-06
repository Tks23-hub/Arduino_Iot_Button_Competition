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