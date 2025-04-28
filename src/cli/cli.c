#include "cli.h"

#include "../os/os.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clear() {
    const int os = getOperatingSystem();

    switch(os) {
        case Windows:
            system("cls");
            return 1;
        case macOS:
        case Linux:
            system("clear");
            return 1;
        case unknown:
            system("clear");
            return -1;
    }

    return -1;
}

int print(const char* text) {
    fputs(text, stdout);
    fflush(stdout);

    return 0;
}

int printCentered(const char* text) {
    int width = getTerminalWidth();
    
    if (width == -1) {
        return -1;
    }

    int textLength = strlen(text);
    int padding = (width - textLength) / 2;

    for (int i = 0; i < padding; i++) {
        fputc(' ', stdout);
    }

    return print(text);
}