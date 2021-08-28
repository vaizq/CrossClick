#ifdef __WIN32

#include <stdio.h>
#include "windows_utils.h"


Vec2 Mouse::Pos()
{
    Vec2 pos;
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    pos.x = (float)cursorPos.x;
    pos.y = (float)cursorPos.y;

    return pos;
}

void Mouse::ClickAt(const Vec2 pos, unsigned int button)
{
    MoveTo(pos);
    Click(button);
}

void Mouse::Click(unsigned int button)
{
    Vec2 pos = MousePos();
    if(button == LEFT)
    {
        mouse_event(LEFT_DOWN, pos.x, pos.y, 0, 0);
        mouse_event(LEFT_UP, pos.x, pos.y, 0, 0);
    }
    else if(button == RIGHT)
    {
        mouse_event(RIGHT_DOWN, pos.x, pos.y, 0, 0);
        mouse_event(RIGHT_UP, pos.x, pos.y, 0, 0);
    }
    else
    {
        printf("Unknown button in Mouse::Click\n");
    }
}

void Mouse::Move(const Vec2 dpos)
{
    Vec2 curPos = Pos();
    SetCursorPos(curPos.x + dpos.x, curPos.y + dpos.y);
}

void Mouse::MoveTo(const Vec2 pos)
{
    SetCursorPos(pos.x, pos.y);
}

void Mouse::SleepMS(unsigned int ms)
{
    Sleep(ms);
}

#endif
