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


void handleRoot() {
  String html;
  html = "<html><body>";
    html += "<h1>Last 10 Button Presses</h1><table border='1'><tr><th>Index</th><th>Duration (ms)</th><th>Shortest</th></tr>";
    for (int i = 0; i < 10; i++) {
      html += "<tr><td>" + String(i + 1) + "</td><td>" + String(pressTimes[i]) + "</td><td>" + (pressTimes[i] == shortestPress ? "Yes" : "No") + "</td></tr>";
    }
    html += "</table>";
  html += "<h1>Shortest Button Press </h1>";
  html += "<p>Shortest Press: " + String(shortestPress) + " ms</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
