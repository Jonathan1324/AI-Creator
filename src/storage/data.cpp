extern "C" {
    #include "data.h"
}
#include <cstdlib>

void initialize_dataSave(DataSave* data, uint16_t input_count, uint16_t output_count, uint64_t num_rules) {
    MetadataSave* metadata = (MetadataSave*)std::malloc(sizeof(MetadataSave));
    data->metadata = metadata;

    initialize_metadata(data->metadata, input_count, output_count);

    AIDataSave* aidata = (AIDataSave*)std::malloc(sizeof(AIDataSave));
    data->aidata = aidata;

    initialize_aidata(data->aidata, metadata->type, num_rules);
}

void destroy_dataSave(DataSave* data) {
    if (!data) return;
    
    destroy_metadata(data->metadata);
    destroy_aidata(data->aidata, data->metadata->type);

    std::free(data->metadata);
    std::free(data->aidata);
}