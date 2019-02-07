#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "wifi-credentials.h"

ESP8266WebServer server(80);

String getContentType(String filename);
bool handleFileRead(String path);
void handlePsPath();

int psValue = 0;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected. IP address: ");
  IPAddress ipAddress = WiFi.localIP();

  Serial.println(ipAddress);

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  SPIFFS.begin();
  
  server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "404: Not Found");
  });

  server.on("/ps", handlePsPath);
  server.begin();
}

void loop() {
  server.handleClient();
}

String getContentType(String filename)
{
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/"))
  {
    path += "index.html";
  }

  String contentType = getContentType(path);
  if (SPIFFS.exists(path))
  {
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }

  Serial.println("\tFile Not Found");
  return false;
}

void handlePsPath()
{
  auto requestMethod = server.method();
  if (requestMethod == HTTP_GET)
  {
    psValue = (psValue + 17) % 1000;
    String psJson = String("{ \"ps\": ") + String(psValue) + String(" }");
    Serial.println(psJson);
    server.send(200, "application/json", psJson);
  }
}
