#include <Arduino.h>
#include "IRCommands.h"
#include "screen.h"

void france_culture() {
  screen_print("France Culture");
  delay(1000);
  IR_hifi_power();
  delay(40000);
  IR_tuner();
  IR_2();
}

void podcast() {
  screen_print("Podcast");
  IR_audio_in();
  for(int i=13;i<35;i++) {
    IR_volume_up();
    delay(1000);
  }
}

