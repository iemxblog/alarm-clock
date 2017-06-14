#include <Time.h>
#include <TimeLib.h>

#include <U8g2lib.h>
#include <IRremote.h>


const int RECV_PIN = 4;
const int LED_PIN = 5;

IRrecv irrecv(RECV_PIN);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
 


enum Code {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_ENTER, KEY_STOP_MODE, KEY_SETUP, KEY_PLAY_PAUSE, KEY_NONE};
enum State {SHOW_TIME, HIDE_TIME, SET_TIME};
State state=SET_TIME;

//              s  s/ m  m/ h  h/ D  D/ M  M/ Y  Y  Y  Y  
int digits[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void shift_buffer(int *buffer)
{
  for(int i=12;i>=0;i--)
    buffer[i+1]=buffer[i];
}

void display()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.setCursor(0, 20);

  u8g2.print(digits[13]);
  u8g2.print(digits[12]);
  u8g2.print(digits[11]);
  u8g2.print(digits[10]);
  u8g2.print("-");
  u8g2.print(digits[9]);
  u8g2.print(digits[8]);
  u8g2.print("-");
  u8g2.print(digits[7]);
  u8g2.print(digits[6]);
  u8g2.println();

  u8g2.setCursor(0, 40);
  
  
  u8g2.print(digits[5]);
  u8g2.print(digits[4]);
  u8g2.print(":");
  u8g2.print(digits[3]);
  u8g2.print(digits[2]);
  u8g2.print(":");
  u8g2.print(digits[1]);
  u8g2.print(digits[0]);
  u8g2.println();
  
  u8g2.sendBuffer();
}

void two_digits(int n)
{
  if(n<10)
    u8g2.print(0);
  u8g2.print(n);
    
}

void display2()
{
  u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.setFont(u8g2_font_fub20_tn);
  u8g2.setCursor(0, 40);

  two_digits(hour());
  u8g2.print(":");
  two_digits(minute());
  u8g2.print(":");
  two_digits(second());

  u8g2.sendBuffer();
}

void clear()
{
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void toggleLED()
{
  static bool led_state = false;
  if(led_state == false) {
    digitalWrite(LED_PIN, HIGH);
    led_state = true;
  }
  else {
    digitalWrite(LED_PIN, LOW);
    led_state = false;
  }
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  u8g2.begin();
  pinMode(LED_PIN, OUTPUT);
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

void loop() {
   
  Code key = getKey();

  if(key == KEY_PLAY_PAUSE)
    toggleLED();
  
  switch(state) {
    case SHOW_TIME:
      display2();
      if(key == KEY_STOP_MODE)
        state = HIDE_TIME;
      else if(key == KEY_SETUP)
        state = SET_TIME;
      break;
    case HIDE_TIME:
      if(key == KEY_STOP_MODE)
        state = SHOW_TIME;
      clear();
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
      display();
      break;
    default:
      break;
  }
}
