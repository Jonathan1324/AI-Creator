#include "save.hpp"

void saveData(Data* data, char* filename) {
    DataSave dataSave;

    initialize_dataSave(&dataSave, data->metadata->input_count, data->metadata->output_count, data->aidata->ruleset->rule_count);

    convertMetadataToMetadataSave(&dataSave, data);

    convertAIDataToAIDataSave(&dataSave, data);

    writeFile(filename, &dataSave);

    destroy_dataSave(&dataSave);
}

void loadData(Data* data, char* filename) {
    DataSave dataSave;

    MetadataSave* metadata = (MetadataSave*)malloc(sizeof(MetadataSave));
    dataSave.metadata = metadata;

    AIDataSave* aidata = (AIDataSave*)malloc(sizeof(AIDataSave));
    dataSave.aidata = aidata;

    readFile(filename, &dataSave);

    

    destroy_dataSave(&dataSave);
}