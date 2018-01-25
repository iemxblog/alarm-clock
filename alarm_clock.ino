#include <TimeLib.h>
#include <U8g2lib.h>

#include "actions.h"
#include "led.h"
#include "IR.h"
#include "IRMacros.h"
#include "screen.h"

enum State {SHOW_TIME, HIDE_TIME, SET_TIME};
State state=SET_TIME;

//              s  s/ m  m/ h  h/ D  D/ M  M/ Y  Y  Y  Y  
int digits[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void shift_buffer(int *buffer)
{
  for(int i=12;i>=0;i--)
    buffer[i+1]=buffer[i];
}

void setup()
{
  Serial.begin(115200);
  init_IR();
  init_screen();
  init_led();
  analogReference(INTERNAL);
}

void loop() {
  actions();
  Code key = getKey();

  if(key == KEY_PLAY_PAUSE)
    toggleLED();

  if(key == KEY_UP)
    france_culture();

  if(key == KEY_DOWN)
    podcast();

  switch(state) {
    case SHOW_TIME:
      display_time();
      if(key == KEY_STOP_MODE || key == KEY_RETURN)
        state = HIDE_TIME;
      else if(key == KEY_SETUP)
        state = SET_TIME;
      break;
    case HIDE_TIME:
      if(key == KEY_STOP_MODE || key == KEY_RETURN)
        state = SHOW_TIME;
      black_screen();
      break;
    case SET_TIME:
      if(key < 10) {
        shift_buffer(digits);
        digits[0]=key;
        
      }
      else if(key==KEY_ENTER) {
        setTime(digits[5]*10+digits[4],digits[3]*10+digits[2],digits[1]*10 + digits[0],digits[7]*10+digits[6],digits[9]*10+digits[8],digits[13]*1000 + digits[12]*100+digits[11]*10+digits[10]);
        state = SHOW_TIME;
      }
      else if(key==KEY_SETUP)
        state=SHOW_TIME;
      display_setup(digits);
      break;
    default:
      break;
  }
}
