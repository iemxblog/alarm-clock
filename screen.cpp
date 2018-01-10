#include <U8g2lib.h>
#include <Time.h>
#include "temperature.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void init_screen()
{
  u8g2.begin();
}

void black_screen()
{
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void two_digits(int n)
{
  if(n<10)
    u8g2.print(0);
  u8g2.print(n);
    
}

void display_time()
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

  u8g2.setFont(u8g2_font_7x14_tr);
  u8g2.setCursor(100, 60);
  u8g2.print(String(temperature()) + "°");

  u8g2.sendBuffer();
}

void display_setup(int digits[])
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
