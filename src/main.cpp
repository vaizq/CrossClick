#include <iostream>
#include <string>

#include "linux_utils.h"

int main(int argc, char** argv)
{
    Display* display = XOpenDisplay(NULL); 
    if(display == NULL)
    {
        std::cout << "Can't open display!" << std::endl;
        return -1;
    }
    Vec2 posA(100, 100);
    Vec2 posB(1000, 1000); 
    while(1)
    {
        Click(display, Button1);
        SleepMS(2000);
    }
    XCloseDisplay(display);
    return 0;
}
