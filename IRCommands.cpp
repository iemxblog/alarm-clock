#include "IR.h"

void IR_hifi_power()
{
  sendNecCode(0x659A38C7);
}

void IR_tuner()
{
  sendNecCode(0x659AB04F);
}

void IR_volume_up()
{
  sendNecCode(0x659A50AF);
}

void IR_volume_down()
{
  sendNecCode(0x659AD02F);
}

void IR_2()
{
  sendNecCode(0x659A807F);
}

void IR_audio_in()
{
  sendNecCode(0x659A32CD);
}
