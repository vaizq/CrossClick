#include "linux_utils.h"

#include <iostream>

Vec2 MousePos()
{
    Vec2 pos;

    XEvent event;
    XQueryPointer (display, DefaultRootWindow (display),
                 &event.xbutton.root, &event.xbutton.window,
                 &event.xbutton.x_root, &event.xbutton.y_root,
                 &event.xbutton.x, &event.xbutton.y,
                 &event.xbutton.state);
    pos.x = event.xbutton.x;
    pos.y = event.xbutton.y;

    return pos; 
}


void Click(unsigned int button)
{
    // Create and setting up the event
    XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
      event.xbutton.window = event.xbutton.subwindow;
      XQueryPointer (display, event.xbutton.window,
             &event.xbutton.root, &event.xbutton.subwindow,
             &event.xbutton.x_root, &event.xbutton.y_root,
             &event.xbutton.x, &event.xbutton.y,
             &event.xbutton.state);
    }

    // Press
    event.type = ButtonPress;
    if (XSendEvent (display, PointerWindow, True, ButtonPressMask, &event) == 0)
    {
        fprintf (stderr, "Error to send the event!\n");
    }
    XFlush (display);
    usleep (100);
    // Release
    event.type = ButtonRelease;
    if (XSendEvent (display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
    {
        fprintf (stderr, "Error to send the event!\n");
    }
    XFlush (display);
    usleep (1);
}

void Move(const Vec2 dpos)
{
    XWarpPointer (display, None, None, 0,0,0,0, dpos.x, dpos.y);
    XFlush (display);
    usleep (1);
}

void MoveTo(const Vec2 pos)
{
    Vec2 curPos = MousePos();
    XWarpPointer (display, None, None, 0,0,0,0,
            pos.x - curPos.x, pos.y - curPos.y);
    XFlush (display);
    usleep (1);
}

void SleepMS(unsigned int ms)
{
    usleep(1000 * ms);
}




