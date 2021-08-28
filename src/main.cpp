#include <iostream>
#include <string>

#ifdef _WIN32
#define OS_Windows
#include <windows.h>
#elif __linux__
#include <unistd.h>    // sleep and usleep
#include <X11/Xlib.h>  // X11
#include <X11/Xutil.h> // XGetPixel and XDestroyImage
#endif


struct Vec2
{
    double x, y;
};

#ifdef OS_Windows
Vec2 GetMousePos();
#else
Vec2 GetMousePos(Display* display);
#endif

void clickAt(const Vec2 pos);
void clickAt(const double x, const double y);


int main(int argc, char** argv)
{

#ifdef OS_Windows

    std::cout << "This platform is windows." << std::endl;

#else

    std::cout << "This platform is linux." << std::endl;

    Display* display = XOpenDisplay( NULL );
    if(display == NULL)
    {
        std::cout << "Failed to get display object." << std::endl;
        return -1;
    }

    while(1)
    {
        Vec2 mousePos = GetMousePos(display);
        std::cout << "X = " << mousePos.x << " Y = " << mousePos.y << std::endl;
        usleep(1);
    }
    
    XCloseDisplay(display);

#endif

    return 0;
}

#ifdef OS_Windows
Vec2 GetMousePos()
{
    Vec2 mousePos;
    
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    mousePos.x = cursorPos.x;
    mousePos.y = cursorPos.y;

    return mousePos;
}
#else
Vec2 GetMousePos(Display* display)
{
    Vec2 mousePos;

    XEvent event;
    XQueryPointer (display, DefaultRootWindow (display),
             &event.xbutton.root, &event.xbutton.window,
             &event.xbutton.x_root, &event.xbutton.y_root,
             &event.xbutton.x, &event.xbutton.y,
             &event.xbutton.state); 
    mousePos.x = event.xbutton.x;
    mousePos.y = event.xbutton.y;
    return mousePos;
}
#endif









