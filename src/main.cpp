#include <Arduino.h>
#include <U8g2lib.h>
#include "tlixty_gfx.h"
#include "tlixty_inputs.h"

#define slc D3
#define bck D4
#define bzr D6

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, D8, D0);
TlixtyDisplay tlxDisp(&u8g2);
TlixtyInputs tlxInp(D1, D2, slc, bck, bzr, true);

void setup()
{
  Serial.begin(115200);
  tlxDisp.begin();
}

void loop()
{
  tlxDisp.update(&tlxInp);
}
