#ifndef TLIXTY_GFX_H_
#define TLIXTY_GFX_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include "tlixty_inputs.h"

int size = 20;
bool fill = false;

class TlixtyDisplay
{
private:
    U8G2 *u8display;
    unsigned int frame;
    unsigned long time_counter;
    int frameRate;

public:
    TlixtyDisplay(){};
    TlixtyDisplay(U8G2 *_u8display)
    {
        u8display = _u8display;
        frame = 0;
        time_counter = millis();
        frameRate = 30;
    }

    void begin()
    {
        u8display->begin();
        Serial.println("Display initialize!");
    }

    void draw(unsigned int _frame)
    {
        u8display->firstPage();
        do
        {
            (fill) ? u8display->drawDisc(64, 32, size) : u8display->drawCircle(64, 32, size);
        } while (u8display->nextPage());
    };

    void update(TlixtyInputs *tlxInp)
    {
        if (millis() - time_counter > (1000 / frameRate))
        {
            frame += 1;
            frame %= frameRate;
            draw(frame);
            time_counter = millis();
        }
        switch (tlxInp->read())
        {
        case RIGHT:
            size++;
            break;
        case LEFT:
            size--;
            break;
        case SELECT:
            fill = !fill;
            break;
        case BACK:
            fill = false;
            size = 20;
            break;
        }
    }
};

#endif