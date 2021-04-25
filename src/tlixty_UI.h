#ifndef TLIXTY_UI_H_
#define TLIXTY_UI_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include <tlixty_GFX.h>
#include <list>

class tlixtyUIComponent
{
public:
    int x, y;
    tlixtyGFX *gfx;
    tlixtyUIComponent(tlixtyGFX *_gfx, int _x, int _y)
    {
        gfx = _gfx;
        x = _x;
        y = _y;
    };
    virtual void draw() = 0;
    void setX(int newX)
    {
        x = newX;
    };
    void setY(int newY)
    {
        y = newY;
    }
};

class tlixtyTitle : public tlixtyUIComponent
{
private:
    String title;

public:
    tlixtyTitle(tlixtyGFX *_gfx, int _x, int _y, String text) : tlixtyUIComponent(_gfx, _x, _y)
    {
        title = text;
        gfx->u8display->setFont(u8g2_font_7x14B_tf);
    }

    void setTitle(String text)
    {
        title = text;
    }

    void draw()
    {
        gfx->u8display->drawUTF8(x, y, title.c_str());
    }
};

class tlixtyPage
{
private:
    String name;
    tlixtyGFX *gfx;
    std::list<tlixtyUIComponent *> UIComponent;

public:
    tlixtyPage(String _name, tlixtyGFX *_gfx)
    {
        name = _name;
        gfx = _gfx;
    }
    void addComponent(tlixtyUIComponent *tlxComp)
    {
        UIComponent.push_front(tlxComp);
    }
    void draw()
    {
        gfx->u8display->firstPage();
        do
        {
            for (auto element : UIComponent)
            {
                // Serial.println(element.x);
                element->draw();
            }
        } while (gfx->u8display->nextPage());
    }
};
#endif
