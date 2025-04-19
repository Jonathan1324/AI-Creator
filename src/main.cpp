#include <iostream>

#define RULE_BASED 0

extern "C" {
    #include "file.h"
    #include "metadata.h"
}

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

int main() {
    Metadata metadata;

    readFile("metadata.dat", &metadata);

    /*

    initialize_metadata(&metadata, 2, 1);

    strcpy(metadata.name, "Test Metadata");
    metadata.type = RULE_BASED;

    strcpy(metadata.inputs[0].name, "Input 1");
    metadata.inputs[0].id = 0;

    strcpy(metadata.inputs[1].name, "Input 2");
    metadata.inputs[1].id = 1;

    strcpy(metadata.outputs[0].name, "Output 1");
    metadata.outputs[0].id = 0;

    */

    writeFile("test.dat", &metadata);
    
    destroy_metadata(&metadata);

    return 0;
}