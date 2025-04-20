#ifndef DATA_HPP
#define DATA_HPP

#include "metadata.hpp"
#include "aidata.hpp"
#include <memory>

struct Data {
    std::shared_ptr<Metadata> metadata;
    std::shared_ptr<AIData> aidata;
};

void initializeData(Data* data);

#endif