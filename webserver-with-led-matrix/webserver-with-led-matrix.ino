#include <ESP8266WiFi.h>
#include "wifi-credentials.h"
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 15
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

WiFiServer server(80);

void setup() {
  Serial.begin(115200); // For debugging output

  initLedMatrix(ledMatrix);

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
  setLedMatrixMessage(ledMatrix, DisplayAddress(ipAddress));

  server.begin();
}

void loop() {
  ledMatrix.clear();
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit(); // commit transfers the byte buffer to the displays

  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }

  Serial.println("New client - enter a message");
  String message = client.readStringUntil('\r');
  setLedMatrixMessage(ledMatrix, message);
  Serial.println(message);
  client.flush();

  client.stop();
  Serial.println("Client disconnected.");
}

void initLedMatrix(LedMatrix& ledMatrix)
{
  ledMatrix.init();
  ledMatrix.setIntensity(1); // range is 0-15
  ledMatrix.setRotation(true);
}

void setLedMatrixMessage(LedMatrix& ledMatrix, String message)
{
  ledMatrix.setText(message);
}

String DisplayAddress(const IPAddress& address)
{
  return String(address[0]) + "." + String(address[1]) + "." +
         String(address[2]) + "." + String(address[3]);
}
