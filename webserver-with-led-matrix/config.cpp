#include <EEPROM.h>
#include "config.h"

const unsigned int EepromBaseAddress = 0;
const unsigned int EepromBlockSize = 512;

void ReadConfig(DisplayConfig& config)
{
  EEPROM.begin(EepromBlockSize);
  EEPROM.get(EepromBaseAddress, config);
}

void WriteConfig(const DisplayConfig& config)
{
  EEPROM.begin(EepromBlockSize);
  EEPROM.put(EepromBaseAddress, config);
  EEPROM.commit();
}
