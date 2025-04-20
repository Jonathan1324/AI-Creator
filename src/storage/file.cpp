extern "C" {
    #include "file.h"
}
#include <iostream>

int writeAIData(FILE* file, AIDataSave* aidata, uint8_t type) {
    switch(type) {
        case RULE_BASED:
            write_ruleset(file, aidata->ruleset);
            return 1;
        default:
            break;
    }
    return 0;
}

int readAIData(FILE* file, AIDataSave* aidata, uint8_t type) {
    switch (type) {
        case RULE_BASED:
            read_ruleset(file, aidata->ruleset);
            return 1;
        
        default:
            break;
    }
    return 0;
}

int readFile(const char* filename, DataSave* data) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cerr << "Error opening file for reading." << std::endl;
        return 1;
    }

    if (!read_metadata(file, data->metadata)) {
        std::cerr << "Error reading metadata." << std::endl;
        fclose(file);
        return 1;
    }

    if (!readAIData(file, data->aidata, data->metadata->type)) {
        std::cerr << "Error reading aidata." << std::endl;
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}

int writeFile(const char* filename, DataSave* data) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    write_metadata(file, data->metadata);

    writeAIData(file, data->aidata, data->metadata->type);

    fclose(file);

    return 0;
}