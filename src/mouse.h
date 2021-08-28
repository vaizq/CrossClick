#ifndef MY_MOUSE_H
#define MY_MOUSE_H

#include "common.h"

class Mouse
{
    Mouse();
    
    void Click();
    void Translate(const Vec2 dpos);
    void SetPos(const Vec2 pos);
    Vec2 Pos();
}


#endif
