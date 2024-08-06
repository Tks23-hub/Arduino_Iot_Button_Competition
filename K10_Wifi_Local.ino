#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

  IPAddress apIP(11, 12, 13, 14);
  const char* ssid = "Amro Soliman";
  const char* password = "88888888";
ESP8266WebServer server(80);
void wifiSetup() {

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  Serial.println("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
}

void wifi_loop() {
  server.handleClient();
}