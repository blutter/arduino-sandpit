#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi-credentials.h"
#include "LedMatrix.h"

#include "message-form.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 15
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

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

  server.on("/", handleRootPath);
  server.begin();
}

void loop() {
  ledMatrix.clear();
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit(); // commit transfers the byte buffer to the displays

  server.handleClient();
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

void handleRootPath()
{
  auto requestMethod = server.method();
  if (requestMethod == HTTP_GET)
  {
    sendMessageForm();
  }
  else if (requestMethod == HTTP_POST)
  {
    Serial.println("post received");
    if (server.hasArg("message"))
    {
      String message = server.arg("message");
      Serial.print("message =");
      Serial.println(message);

      setLedMatrixMessage(ledMatrix, message);
      sendMessageForm();
    }
  }
}

void sendMessageForm()
{
  server.send(200, "text/html", messageHtml);
}