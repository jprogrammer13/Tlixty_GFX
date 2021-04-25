#ifndef TLIXTY_INPUTS_H_
#define TLIXTY_INPUTS_H_

#include <Arduino.h>
#include "ESPRotary.h"

enum action // action list with int identificator
{
    NONE,
    BACK,
    BACK_HOLD,
    SELECT,
    SELECT_HOLD,
    LEFT,
    RIGHT
};

class TlixtyButton
{
private:
    uint8_t pin;
    int clicked;
    int lastState;
    unsigned long wait;
    unsigned long startClick;

public:
    TlixtyButton(){};
    TlixtyButton(uint8_t _pin, unsigned long _wait = 100)
    {
        pin = _pin;
        pinMode(pin, INPUT_PULLUP);
        clicked = 0;
        lastState = 0;
        wait = _wait;
    }

    void read()
    {

        clicked = 0;
        int currentState = !digitalRead(pin);
        if (currentState && !lastState)
        {
            lastState = 1;
            startClick = millis();
            clicked = 1;
        }
        if (!currentState && millis() - startClick > wait)
        {
            lastState = 0;
        }
    }

    int getState()
    {
        return clicked;
    }
};

class TlixtyInputs
{
private:
    ESPRotary *encoder;
    TlixtyButton slc;
    TlixtyButton bck;
    uint8_t bzr;
    bool tone;
    unsigned long timer;

public:
    TlixtyInputs(){};
    TlixtyInputs(uint8_t p1, uint8_t p2, uint8_t _slc, byte _bck, uint8_t _bzr, bool _tone)
    {
        encoder = new ESPRotary(p1, p2);
        bzr = _bzr;
        slc = TlixtyButton(_slc);
        bck = TlixtyButton(_bck);
        pinMode(bzr, OUTPUT);
        tone = _tone;
        timer = millis();
    }

    int read()
    {
        action result;
        encoder->loop();
        int knob = encoder->getDirection();
        slc.read();
        bck.read();

        if (knob == RE_RIGHT)
        {
            result = RIGHT;
        }
        else if (knob == RE_LEFT)
        {
            result = LEFT;
        }
        else if (slc.getState())
        {
            result = (result != SELECT) ? SELECT : NONE;
        }
        else if (bck.getState())
        {
            result = (result != BACK) ? BACK : NONE;
        }
        else
        {
            result = NONE;
        }

        encoder->resetPosition();
        return result;
    };
};

#endif