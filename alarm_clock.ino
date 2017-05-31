#include <IRremote.h>

const int RECV_PIN = 4;
const int led = 5;

IRrecv irrecv(RECV_PIN);



enum Code {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_ENTER, KEY_NONE};

int digits[] = {0, 0, 0, 0, 0, 0};

void shift_buffer(int *buffer)
{
  for(int i=4;i>=0;i--)
    buffer[i+1]=buffer[i];
}

void display()
{
  Serial.print(digits[5]);
  Serial.print(digits[4]);
  Serial.print(":");
  Serial.print(digits[3]);
  Serial.print(digits[2]);
  Serial.print(":");
  Serial.print(digits[1]);
  Serial.print(digits[0]);
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
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
  if(key==1)
    digitalWrite(led, HIGH);
  else if(key==2)
    digitalWrite(led, LOW);
  delay(200);
}
