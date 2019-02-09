#ifndef __CONFIG_H
#define __CONFIG_H

#include <Arduino.h>

struct DisplayConfig {
  byte brightness;
  unsigned long scrollDelayMs;
  char message[200];
  char messageTerminator = '\0';
};

void ReadConfig(struct DisplayConfig& config);
void WriteConfig(const struct DisplayConfig& config);

#endif