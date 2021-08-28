#include <iostream>
#include <string>

#include "common.h"

#ifdef __WIN32
#define OS_Windows
#include "windows_utils.h"
#else
#define OS_Linux
#include "linux_utils.h"
#endif

#ifdef OS_Linux
LINUX_BEGIN()
#endif

int main(int argc, char** argv)
{

#ifdef OS_Linux
    LINUX_SETUP()
#endif

    Vec2 velo{ 10, 10 };

    while(1)
    {
        if(MousePos().x < 100)
            velo.x = 10;
        if(MousePos().x > 1700)
            velo.x = -10;
        if(MousePos().y < 100)
            velo.y = 10;
        if(MousePos().y > 1000)
            velo.y = -10;
        Move(velo);
        SleepMS(10);
    }
    XCloseDisplay(display);
    return 0;
}
