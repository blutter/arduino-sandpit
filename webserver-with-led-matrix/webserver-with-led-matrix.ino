#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi-credentials.h"
#include "LedMatrix.h"

#include "message-form.h"
#include "config.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 15
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);
unsigned long scrollDelayMs = 0;
unsigned long previousUpdateTimeMs;

ESP8266WebServer server(80);

struct DisplayConfig config;

#define STARTUP_MESSAGE_DELAY_MS 10000
unsigned long startupTimeMs;
bool isConfigMessageDisplayed;

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

  ReadConfig(config);
  isConfigMessageDisplayed = false;

  server.on("/", handleRootPath);
  server.begin();

  previousUpdateTimeMs = millis();
  startupTimeMs = millis();
}

void loop() {
  auto currentLoopStartTimeMs = millis();

  if (!isStartupPeriod(startupTimeMs, currentLoopStartTimeMs) && !isConfigMessageDisplayed)
  {
    Serial.println("Displaying configured message");
    setLedMatrixMessage(ledMatrix, config.message);
    isConfigMessageDisplayed = true;
  }

  if (isScrollDelayExpired(currentLoopStartTimeMs, previousUpdateTimeMs, scrollDelayMs))
  {
    previousUpdateTimeMs = currentLoopStartTimeMs;

    ledMatrix.clear();
    ledMatrix.scrollTextLeft();
    ledMatrix.drawText();
    ledMatrix.commit(); // commit transfers the byte buffer to the displays
  }

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
  Serial.print("Message = ");
  Serial.println(message);
  ledMatrix.setText(message);
}

String DisplayAddress(const IPAddress& address)
{
  return String(address[0]) + "." + String(address[1]) + "." +
         String(address[2]) + "." + String(address[3]);
}

bool isStartupPeriod(unsigned long startupTimeMs, unsigned long currentTimeMs) 
{
  return (currentTimeMs - startupTimeMs) < STARTUP_MESSAGE_DELAY_MS;
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
    if (server.hasArg("message") && server.hasArg("delayMs"))
    {
      String message = server.arg("message");
      Serial.print("message = ");
      Serial.println(message);

      String delayMsStr = server.arg("delayMs");
      Serial.print("delayMs = ");
      auto delayMs = delayMsStr.toInt();
      delayMs = (delayMs < 0) ? 0 : delayMs;
      Serial.println(delayMs);

      scrollDelayMs = delayMs;

      setLedMatrixMessage(ledMatrix, message);
      sendMessageForm();

      message.toCharArray(config.message, sizeof(config.message));
      WriteConfig(config);
    }
  }
}

void sendMessageForm()
{
  server.send(200, "text/html", messageHtml);
}

bool isScrollDelayExpired(
  unsigned long currentLoopStartTimeMs, 
  unsigned long previousUpdateTimeMs, 
  unsigned long scrollDelayMs)
{
  return (currentLoopStartTimeMs - previousUpdateTimeMs) >= scrollDelayMs;
}