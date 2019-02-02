#include <EEPROM.h>

const uint EepromBaseAddress = 0;
const uint EepromBlockSize = 512;

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