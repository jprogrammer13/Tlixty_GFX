#ifndef TLIXTY_DISPLAY_H_
#define TLIXTY_DISPLAY_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include "tlixty_GFX.h"
#include "tlixty_inputs.h"
int r = 1;

class TlixtyDisplay
{
private:
    U8G2 *u8display;
    tlixtyGFX tlxGFX;
    unsigned int frame;
    unsigned long time_counter;
    unsigned long frameRate;

public:
    TlixtyDisplay(){};
    TlixtyDisplay(U8G2 *_u8display)
    {
        u8display = _u8display;
        tlxGFX = tlixtyGFX(u8display);
        frame = 0;
        time_counter = millis();
        frameRate = 60;
    }

    void begin()
    {
        tlxGFX.begin();
        Serial.println("Display initialize!");
    }

    void draw(unsigned int _frame){};

    void update(TlixtyInputs *tlxInp)
    {
        
    };
};

#endif