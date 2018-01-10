#include <Arduino.h>
#include <IRremote.h>
#include "IR.h"

const int RECV_PIN = 4;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

void init_IR()
{
    irrecv.enableIRIn();
}

enum Code getKey() {
  
  decode_results results;
  enum Code ret=KEY_NONE;
  
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0xFD30CF:
        ret = KEY_0;
        break;
      case 0xFD08F7:
        ret = KEY_1;
        break;
      case 0xFD8877:
        ret = KEY_2;
        break;
      case 0xFD48B7:
        ret = KEY_3;
        break;
      case 0xFD28D7:
        ret = KEY_4;
        break;
      case 0xFDA857:
        ret = KEY_5;
        break;
      case 0xFD6897:
        ret = KEY_6;
        break;
      case 0xFD18E7:
        ret = KEY_7;
        break;
      case 0xFD9867:
        ret = KEY_8;
        break;
      case 0xFD58A7:
        ret = KEY_9;
        break;
      case 0xFD906F:
        ret = KEY_ENTER;
        break;
      case 0xFD609F:
        ret = KEY_STOP_MODE;
        break;
      case 0xFD20DF:
        ret = KEY_SETUP;
        break;
      case 0xFD807F:
        ret = KEY_PLAY_PAUSE;
        break;
      case 0xFDA105F:
        ret = KEY_UP;
        break;
      case 0xFDB04F:
        ret = KEY_DOWN;
        break;
      case 0xFD10EF:
        ret=KEY_LEFT;
        break;
      case 0xFD50AF:
        ret = KEY_RIGHT;
        break;
      case 0x659A05FA:
        ret = KEY_IPOD_CONTROL;  // available on the second remote
        break;
      case 0x659ACE31:
        ret = KEY_RETURN;
        break;
      default:
        Serial.println("debug");
        Serial.println(results.value, HEX);
        ret = KEY_NONE;
        break;
    }
    delay(200);
    irrecv.resume(); // Receive the next value
  }
  return ret;
}

void sendNecCode(uint32_t code)
{
  Serial.print("Sending code ");
  Serial.print(code, HEX);
  Serial.print(" on pin ");
  Serial.println(SEND_PIN);
  irsend.sendNEC(code, 32);
  delay(20);
  irsend.sendNEC(code, 32);
  delay(200);
  irrecv.enableIRIn();
}

