#ifndef LINUX_UTILS_H
#define LINUX_UTILS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "common.h"

constexpr unsigned int LEFT_CLICK = Button1;
constexpr unsigned int RIGHT_CLICK = Button2; // Not sure about this
// Mouse wheel stuff is button3..5

// Returns current mouse pointer position
Vec2 MousePos(Display* display);

// Clicks specified button at specified position
void ClickAt(const Vec2 pos, unsigned int button);

// Clicks mouse button at current position
void Click(Display* display, unsigned int button);

// Move mouse pointer (relative)
void Move(Display* display, const Vec2 dpos);

// Move mouse pointer (absolute)
void MoveTo(Display* display, const Vec2 pos);

// Sleep ms milliseconds
void SleepMS(unsigned int ms);


#endif
