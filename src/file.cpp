extern "C" {
    #include "file.h"
}
#include <iostream>

int readFile(const char* filename, Metadata* metadata) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cerr << "Error opening file for reading." << std::endl;
        return 1;
    }

    if (!read_metadata(file, metadata)) {
        std::cerr << "Error reading metadata." << std::endl;
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}

int writeFile(const char* filename, Metadata* metadata) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    write_metadata(file, metadata);

    fclose(file);

    return 0;
}