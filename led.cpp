#include <Arduino.h>

const int LED_PIN = 6;
bool led_state = false;

void init_led()
{
  pinMode(LED_PIN, OUTPUT);
}

void ledOn()
{
  digitalWrite(LED_PIN, HIGH);
  led_state=true;
}

void ledOff()
{
  digitalWrite(LED_PIN, LOW);
  led_state=false;
}

void toggleLED()
{
  if(led_state == false)
    ledOn();
  else
    ledOff();
}
