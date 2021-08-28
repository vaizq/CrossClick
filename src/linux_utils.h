#ifndef LINUX_UTILS_H
#define LINUX_UTILS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "common.h"

namespace Mouse
{
constexpr unsigned int LEFT = Button1;
constexpr unsigned int RIGHT = Button2; // Not sure about this
}
// Mouse wheel stuff is button3..5


extern Display* display;

// Call this macro before using any of these functions

#define LINUX_BEGIN() Display* display; 
#define LINUX_SETUP() display=XOpenDisplay(NULL);if(display == NULL){printf("Can't open display.");return-1;}
#define LINUX_END() XCloseDisplay(display);

namespace Mouse
{

// Returns current mouse pointer position
Vec2 Pos();

// Clicks specified button at specified position
void ClickAt(const Vec2 pos, unsigned int button);

// Clicks mouse button at current position
void Click(unsigned int button);

// Move mouse pointer (relative)
void Move(const Vec2 dpos);

// Move mouse pointer (absolute)
void MoveTo(const Vec2 pos);

// Sleep ms milliseconds
void SleepMS(unsigned int ms);

}

#endif
