#include <Arduino.h>
#include <U8g2lib.h>
#include "tlixty_display.h"
#include "tlixty_inputs.h"
#include "tlixty_UI.h"

#define slc D3
#define bck D4
#define bzr D6

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, D8, D0);
TlixtyInputs tlxInp(D1, D2, slc, bck, bzr, true);

tlixtyGFX tlxGFX(&u8g2);
tlixtyPage testPage("Test Page", &tlxGFX);

void setup()
{
  Serial.begin(115200);
  tlxGFX.begin();
  testPage.addComponent(new tlixtyTitle(&tlxGFX, 5, 50, "Titolo di test"));
  testPage.addComponent(new tlixtyTitle(&tlxGFX, 5, 25, "Titolo di test 2"));
  testPage.addComponent(new tlixtyCircle(&tlxGFX, 128 / 2, 64 / 2, 10));
  testPage.addComponent(new tlixtyCircle(&tlxGFX, 128 / 2, 64 / 2, 20, 3));
}

void loop()
{
  testPage.draw();
}
