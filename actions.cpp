#include <Time.h>
#include <IRremote.h>
#include "led.h"
//IRsend irsend;

void actions()
{
  //if(hour()==0 && minute() == 30 && second() == 0)
  // irsend.sendNEC(0x659A38C7, 32);

  if(hour() == 23 && minute() == 0 && second() == 0)
    ledOn();
  if(hour() == 0 && minute() == 30 && second() == 0)
    ledOff();
  
}

