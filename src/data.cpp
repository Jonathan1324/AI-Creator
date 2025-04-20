extern "C" {
    #include "data.h"
}
#include <cstdlib>

void initialize_data(Data* data, uint16_t input_count, uint16_t output_count, uint64_t num_rules) {
    Metadata* metadata = (Metadata*)std::malloc(sizeof(Metadata));
    data->metadata = metadata;

    initialize_metadata(data->metadata, input_count, output_count);

    AIData* aidata = (AIData*)std::malloc(sizeof(AIData));
    data->aidata = aidata;

    initialize_aidata(data->aidata, metadata->type, num_rules);
}

void destroy_data(Data* data) {
    if (!data) return;
    
    destroy_metadata(data->metadata);
    destroy_aidata(data->aidata, data->metadata->type);

    std::free(data->metadata);
    std::free(data->aidata);
}