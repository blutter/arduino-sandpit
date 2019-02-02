#include "cp437font.h"
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 15
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

/*
 * Sample from
 * https://github.com/squix78/MAX7219LedMatrix
 * 
 * Connections:
 * MAX7219 ESP8266 NodeMCU devkit
 * VCC +3.3V 3V3
 * GND GND GND
 * DIN HSPID/HMOSI D7
 * CS  HSPICS/HCS  D8 (Arduino pin 15)
 * CLK HSPICLK/HSCLK D5
 */

void setup() {
  Serial.begin(115200); // For debugging output
  ledMatrix.init();
  ledMatrix.setIntensity(1); // range is 0-15
  ledMatrix.setRotation(true);
  ledMatrix.setText("Hello world!!");
}

void loop() {
  ledMatrix.clear();
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit(); // commit transfers the byte buffer to the displays
  //delay(1);
}
