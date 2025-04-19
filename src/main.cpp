#include <iostream>

#define RULE_BASED 0

extern "C" {
    #include "file.h"
    #include "data.h"
}

int main() {
    Data data;

    Metadata* metadata = new Metadata();
    data.metadata = metadata;

    initialize_metadata(data.metadata, 2, 1);

    strcpy(metadata->name, "Test Metadata");
    metadata->type = RULE_BASED;


    AIData* aidata = new AIData();
    data.aidata = aidata;

    



    strcpy(metadata->inputs[0].name, "Input 1");
    metadata->inputs[0].id = 0;

    strcpy(metadata->inputs[1].name, "Input 2");
    metadata->inputs[1].id = 1;

    strcpy(metadata->outputs[0].name, "Output 1");
    metadata->outputs[0].id = 0;

    writeFile("metadata.dat", &data);

    destroy_data(&data);

    delete metadata;
    delete aidata;

    return 0;
}