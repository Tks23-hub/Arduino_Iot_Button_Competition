#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>            
#include <ESP8266HTTPClient.h>
            
const char* ssd = "TKS-23";
const char* pswd = "Adham2003@";
            
WiFiClient client;
int server_port = 80;

void wifiClient_Setup() {
    Serial.println("wifiSetup");
    WiFi.begin(ssd,pswd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("trying ...");
        delay(100);
    }
    Serial.println("Connected to network");
 }
   
  void SendData(int val) {
  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=SET&DEV=1121&CH=1&VAL=" + String(val);
  Serial.println("Full URL: " + dataURL);
  HTTPClient http;
  http.begin(client, dataURL);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("HTTP Code: " + String(httpCode)); 
  } else {
    Serial.println("HTTP request failed, Send: " + String(httpCode));
  }
  
  http.end();
}
 unsigned long GetData() {
  HTTPClient http;
  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=GET&DEV=1121&CH=1";
 
  http.begin(client, dataURL);
  
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("HTTP Code: " + String(httpCode));
    String payload = http.getString();
    Serial.println(payload.toInt());
        if (payload.length() > 0) {
      return payload.toInt();
    }
  } else {
    Serial.println("HTTP request failed,  GET : " + String(httpCode));
  }
  
  http.end();
  return 0xFFF; 
}