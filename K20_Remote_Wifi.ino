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
   