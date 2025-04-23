#include "save.hpp"
#include <iostream>

void saveData(Data* data, const char* filename) {
    DataSave dataSave;

    initialize_dataSave(&dataSave, data->metadata->input_count, data->metadata->output_count, data->aidata->ruleset->rule_count);

    convertMetadataToMetadataSave(&dataSave, data);

    convertAIDataToAIDataSave(&dataSave, data);

    writeFile(filename, &dataSave);

    destroy_dataSave(&dataSave);
}

void loadData(Data* data, const char* filename) {
    DataSave dataSave;

    MetadataSave* metadata = (MetadataSave*)malloc(sizeof(MetadataSave));
    dataSave.metadata = metadata;

    AIDataSave* aidata = (AIDataSave*)malloc(sizeof(AIDataSave));
    dataSave.aidata = aidata;

    RuleSetSave* ruleset = (RuleSetSave*)malloc(sizeof(RuleSetSave));
    aidata->ruleset = ruleset;

    readFile(filename, &dataSave);

    convertMetadataSaveToMetadata(&dataSave, data);

    convertAIDataSaveToAIData(&dataSave, data);

    destroy_dataSave(&dataSave);
}