#include "data.hpp"


void initializeData(Data* data) {
    std::shared_ptr<Metadata> metadata = std::make_shared<Metadata>();
    data->metadata = metadata;

    std::shared_ptr<AIData> aidata = std::make_shared<AIData>();

    aidata->ruleset = nullptr;

    switch (data->metadata->type) {
        case 0:
            aidata->ruleset = std::make_shared<RuleSet>();
            break;
        default:
            break;
    }

    data->aidata = aidata;
}

void convertDataToSaveData(DataSave* dataSave, Data* data) {
    strncpy(dataSave->metadata->name, data->metadata->name, std::min(std::strlen(data->metadata->name), sizeof(dataSave->metadata->name)));
    dataSave->metadata->type = data->metadata->type;

    for(int i = 0; i < data->metadata->input_count; i++) {
        strncpy(dataSave->metadata->inputs[i].name, data->metadata->inputs.at(i).name, std::min(std::strlen(data->metadata->inputs.at(i).name), sizeof(dataSave->metadata->inputs[i].name)));
        dataSave->metadata->inputs[i].id = data->metadata->inputs.at(i).id;
    }

    for(int i = 0; i < data->metadata->output_count; i++) {
        strncpy(dataSave->metadata->outputs[i].name, data->metadata->outputs.at(i).name, std::min(std::strlen(data->metadata->outputs.at(i).name), sizeof(dataSave->metadata->outputs[i].name)));
        dataSave->metadata->outputs[i].id = data->metadata->outputs.at(i).id;
    }
}