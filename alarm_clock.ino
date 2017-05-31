#include <U8g2lib.h>
#include <IRremote.h>


const int RECV_PIN = 4;

IRrecv irrecv(RECV_PIN);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
 


enum Code {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_ENTER, KEY_PLAY, KEY_STOP, KEY_NONE};

int digits[] = {0, 0, 0, 0, 0, 0};

bool show = false;

void shift_buffer(int *buffer)
{
  for(int i=4;i>=0;i--)
    buffer[i+1]=buffer[i];
}

void display()
{
  u8g2.print(digits[5]);
  u8g2.print(digits[4]);
  u8g2.print(":");
  u8g2.print(digits[3]);
  u8g2.print(digits[2]);
  u8g2.print(":");
  u8g2.print(digits[1]);
  u8g2.print(digits[0]);
  u8g2.println();
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  u8g2.begin();
}



enum Code getKey() {
  
  decode_results results;
  enum Code ret=KEY_NONE;
  
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0x659A906F:
        ret = KEY_0;
        break;
      case 0x659A00FF:
        ret = KEY_1;
        break;
      case 0x659A807F:
        ret = KEY_2;
        break;
      case 0x659A40BF:
        ret = KEY_3;
        break;
      case 0x659AC03F:
        ret = KEY_4;
        break;
      case 0x659A20DF:
        ret = KEY_5;
        break;
      case 0x659AA05F:
        ret = KEY_6;
        break;
      case 0x659A609F:
        ret = KEY_7;
        break;
      case 0x659AE01F:
        ret = KEY_8;
        break;
      case 0x659A10EF:
        ret = KEY_9;
        break;
      case 0x659A2ED1:
        ret = KEY_ENTER;
        break;
      case 0x659AAE51:
        ret = KEY_PLAY;
        break;
      case 0x659A09F6:
        ret = KEY_STOP;
        break;
      default:
        Serial.println("debug");
        Serial.println(results.value, HEX);
        ret = KEY_NONE;
        break;
    }
    irrecv.resume(); // Receive the next value
  }
  return ret;
}

void loop() {
  Code key = getKey();
  if(key < 10) {
    shift_buffer(digits);
    digits[0]=key;
    display();
  }
  else if(key == KEY_PLAY)
    show = true;
  else if(key == KEY_STOP)
    show = false;
    
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.setCursor(0, 20);
  if(show)
    display();
  u8g2.sendBuffer();
  delay(200);
}
