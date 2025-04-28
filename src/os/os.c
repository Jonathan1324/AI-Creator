#include "os.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#endif

int getOperatingSystem() {
    #ifdef _WIN32
        return Windows;
    #elif defined(__APPLE__)
        return macOS;
    #elif defined(__linux__)
        return Linux;
    #else
        return unknown;
    #endif
}

int getTerminalWidth() {
    #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.dwSize.X;
    }
    return -1;
    #else
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        return -1;
    }
    return ws.ws_col;
    #endif
}