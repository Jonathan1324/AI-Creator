#include "save.hpp"
#include <iostream>

int saveData(Data* data, const char* filename) {
    DataSave dataSave;

    initialize_dataSave(&dataSave, data->metadata->input_count, data->metadata->output_count, data->aidata->ruleset->rule_count);

    convertMetadataToMetadataSave(&dataSave, data);

    convertAIDataToAIDataSave(&dataSave, data);

    if(writeFile(filename, &dataSave)) {
        return 1;
    }

    destroy_dataSave(&dataSave);

    return 0;
}

int loadData(Data* data, const char* filename) {
    DataSave dataSave;

    MetadataSave* metadata = (MetadataSave*)malloc(sizeof(MetadataSave));
    dataSave.metadata = metadata;

    AIDataSave* aidata = (AIDataSave*)malloc(sizeof(AIDataSave));
    dataSave.aidata = aidata;

    RuleSetSave* ruleset = (RuleSetSave*)malloc(sizeof(RuleSetSave));
    aidata->ruleset = ruleset;

    int status = readFile(filename, &dataSave);

    if(status != 0) {
        return status;
    }

    convertMetadataSaveToMetadata(&dataSave, data);

    convertAIDataSaveToAIData(&dataSave, data);

    destroy_dataSave(&dataSave);

    return 0;
}