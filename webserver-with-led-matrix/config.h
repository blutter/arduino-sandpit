struct {
  byte brightness;
  unsignedLong scrollDelayMs;
  char message[200];
  char messageTerminator = '\0';
} DisplayConfig;

void ReadConfig(DisplayConfig& config);
void WriteConfig(const DisplayConfig& config);