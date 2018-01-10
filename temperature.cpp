#include <Arduino.h>

const int LM35DZ_PIN = 0;

float temperature()
{
  return (2.56 * analogRead(LM35DZ_PIN) * 100.0) / 1024;
}

