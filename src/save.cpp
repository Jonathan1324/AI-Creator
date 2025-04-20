#include "save.hpp"

void saveData(Data* data, char* filename) {
    DataSave dataSave;

    initialize_dataSave(&dataSave, data->metadata->input_count, data->metadata->output_count, data->aidata->ruleset->rule_count);

    convertMetadataToMetadataSave(&dataSave, data);

    convertAIDataToAIDataSave(&dataSave, data);

    writeFile(filename, &dataSave);

    destroy_dataSave(&dataSave);
}