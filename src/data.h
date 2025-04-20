#ifndef DATA_H
#define DATA_H

#include "metadata.h"
#include "aidata.h"

typedef struct {
    Metadata* metadata;
    AIData* aidata;
} Data;

void initialize_data(Data* data,
                     uint16_t input_count,
                     uint16_t output_count,
                     uint64_t num_rules);

void destroy_data(Data* data);

#endif