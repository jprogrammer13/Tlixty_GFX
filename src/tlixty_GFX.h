#ifndef TLIXTY_GFX_H_
#define TLIXTY_GFX_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include <math.h>

class tlixtyGFX
{
public:
    U8G2 *u8display;
    tlixtyGFX(){};
    tlixtyGFX(U8G2 *_u8display)
    {
        u8display = _u8display;
    }
    void begin()
    {
        u8display->begin();
    }

    void drawLine(int x0, int y0, int x1, int y1, int thick = 1)
    {
        int counter = 0;
        int new_y0 = y0;
        int new_y1 = y1;

        for (int i = 0; i < thick; i++)
        {
            counter = (i / 2) + (i % 2);
            new_y0 = (i % 2 == 0) ? y0 - counter : y0 + counter;
            new_y1 = (i % 2 == 0) ? y1 - counter : y1 + counter;
            u8display->drawLine(x0, new_y0, x1, new_y1);
        }
    };

    void drawCircle(int x, int y, int r, int thick = 1)
    {
        int counter = 0;
        int new_r = r;

        for (int i = 0; i < thick; i++)
        {
            counter = (i / 2) + (i % 2);
            new_r = (i % 2 == 0) ? r - counter : r + counter;
            u8display->drawCircle(x, y, new_r);
        }
    }

    float rotateX(float x, float r, float d)
    {
        return x + r * cos((d - 90) * 1000.0 / 57296.0);
    }

    float rotateY(float y, float r, float d)
    {
        return y + r * sin((d - 90) * 1000.0 / 57296.0);
    }

    void drawSimpleArc(int x, int y, int r, int start, int stop)
    {
        int steps = 100;
        int x0 = rotateX(x, r, start);
        int y0 = rotateY(y, r, start);

        float arcLen = stop - start;
        for (int i = 0; i < steps; i++)
        {
            float segmentLen = i * (arcLen / steps);
            int x1 = rotateX(x, r, start + segmentLen);
            int y1 = rotateY(y, r, start + segmentLen);
            drawLine(x0, y0, x1, y1);
            x0 = x1;
            y0 = y1;
        }
    }

    void drawArc(int x, int y, int r, int start, int stop, int thick = 1)
    {
        int counter = 0;
        int new_r = r;

        for (int i = 0; i < thick; i++)
        {
            counter = (i / 2) + (i % 2);
            new_r = (i % 2 == 0) ? r - counter : r + counter;
            drawSimpleArc(x, y, new_r, start, stop);
        }
    }
};

#endif