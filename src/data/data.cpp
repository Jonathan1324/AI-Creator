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