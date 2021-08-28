#include "windows_utils.h"


Vec2 MousePos()
{
    Vec2 pos;
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    pos.x = (float)cursorPos.x;
    pos.y = (float)cursorPos.y;

    return pos;
}

void ClickAt(const Vec2 pos, unsigned int button)
{
    SetCursorPos(pos.x, pos.y);
    mouse_event(LEFT_DOWN, pos.x, pos.y);
    mouse_event(LEFT_UP, pos.x, pos.y);
}

void Click(unsigned int button)
{
    Vec2 pos = MousePos();
    mouse_event(LEFT_DOWN, pos.x, pos.y, 0, 0);
    mouse_event(LEFT_UP, pos.x, pos.y);
}

void Move(const Vec2 dpos)
{
    Vec2 curPos = MousePos();
    SetCursorPos(curPos.x + dpos.x, curPos.y + dpos.y);
}

void MoveTo(const Vec2 pos)
{
    SetCursorPos(pos.x, pos.y);
}

void SleepMS(unsigned int ms)
{
    Sleep(ms);
}
