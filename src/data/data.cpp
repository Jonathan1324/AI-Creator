#include "data.hpp"

void initializeData(Data* data) {
    std::shared_ptr<Metadata> metadata = std::make_shared<Metadata>();
    data->metadata = metadata;
}