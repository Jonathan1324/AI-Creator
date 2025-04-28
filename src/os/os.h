#ifndef OS_H
#define OS_H

enum OperatingSystem {
    Windows = 1,
    macOS = 2,
    Linux = 3,
    unknown = -1
};

int getOperatingSystem();

int getTerminalWidth();

#endif