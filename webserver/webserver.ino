#include <ESP8266WiFi.h>
#include "wifi-credentials.h"

WiFiServer server(80);

void setup() {
  Serial.begin(115200); // For debugging output

  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }

  Serial.println("New client - enter a message");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  client.stop();
  Serial.println("Client disconnected.");
}
