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

    while(1)
    {
        Mouse::Click(Mouse::LEFT);
        Mouse::SleepMS(1000);    
    }
#ifdef OS_Linux
    LINUX_END() 
#endif
    return 0;
}
