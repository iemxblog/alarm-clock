#ifndef IR_H
#define IR_H

#include <Arduino.h>

enum Code {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_ENTER, KEY_STOP_MODE, KEY_SETUP, KEY_PLAY_PAUSE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_IPOD_CONTROL, KEY_RETURN, KEY_NONE};
void init_IR();
enum Code getKey();
void sendNecCode(uint32_t);

#endif
