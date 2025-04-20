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

void convertDataToSaveData(DataSave* dataSave, Data* data);

#endif