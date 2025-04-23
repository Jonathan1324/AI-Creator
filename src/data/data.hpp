#ifndef DATA_HPP
#define DATA_HPP

extern "C" {
    #include "../storage/data.h"
}

#include "metadata.hpp"
#include "aidata.hpp"
#include <memory>

struct Data {
    std::shared_ptr<Metadata> metadata;
    std::shared_ptr<AIData> aidata;
};

void initializeData(Data* data);

void convertMetadataToMetadataSave(DataSave* dataSave, Data* data);

void convertAIDataToAIDataSave(DataSave* dataSave, Data* data);


void convertMetadataSaveToMetadata(DataSave* dataSave, Data* data);

void convertAIDataSaveToAIData(DataSave* dataSave, Data* data);

#endif