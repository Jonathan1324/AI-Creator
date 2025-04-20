extern "C" {
    #include "data.h"
}

void initialize_data(Data* data, uint16_t input_count, uint16_t output_count, uint64_t num_rules) {
    Metadata* metadata = new Metadata();
    data->metadata = metadata;

    initialize_metadata(data->metadata, input_count, output_count);

    AIData* aidata = new AIData();
    data->aidata = aidata;

    initialize_aidata(data->aidata, metadata->type, num_rules);
}

void destroy_data(Data* data) {
    if (!data) return;
    
    destroy_metadata(data->metadata);
    destroy_aidata(data->aidata, data->metadata->type);

    delete data->metadata;
    delete data->aidata;
}