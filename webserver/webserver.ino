#include <ESP8266WiFi.h>
#include "wifi-credentials.h"

WiFiServer server(80);

void setup() {
  Serial.begin(115200); // For debugging output

  Serial.println("Connecting to %s", SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected. IP address: %s", WiFi.localIP());
}

void loop() {
}
