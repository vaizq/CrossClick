#ifndef WINDOWS_UTILS_H
#define WINDOWS_UTILS_H

#include <windows.h>

#include "common.h"

namespace Mouse
{
    constexpr unsigned int LEFT = 0;
    constexpr unsigned int RIGHT = 1;
    constexpr unsigned int LEFT_DOWN = MOUSEEVENTF_LEFTDOWN;
    constexpr unsigned int LEFT_UP = MOUSEEVENTF_LEFTUP;
}

namespace Mouse
{
// Returns current position of mouse
Vec2 Pos();

// Clicks specified button at specified position
void ClickAt(const Vec2 pos, unsigned int button);

// Clicks specified button
void Click(unsigned int button);

// Move mouse pointer (relative)
void Move(const Vec2 dpos);

// Move mouse pointer (absolute)
void MoveTo(const Vec2 pos);

// Sleep ms milliseconds
void SleepMS(unsigned int ms);
}

#endif
