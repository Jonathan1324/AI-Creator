#include <iostream>

#define RULE_BASED 0

extern "C" {
    #include "file.h"
    #include "metadata.h"
}

int main() {
    Metadata metadata;

    initialize_metadata(&metadata, 2, 1);

    strcpy(metadata.name, "Test Metadata");
    metadata.type = RULE_BASED;

    strcpy(metadata.inputs[0].name, "Input 1");
    metadata.inputs[0].id = 0;

    strcpy(metadata.inputs[1].name, "Input 2");
    metadata.inputs[1].id = 1;

    strcpy(metadata.outputs[0].name, "Output 1");
    metadata.outputs[0].id = 0;

    const char* filename = "metadata.bin";

    write_metadata(filename, &metadata);

    
    destroy_metadata(&metadata);

    return 0;
}