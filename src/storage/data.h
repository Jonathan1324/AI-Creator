#ifndef DATA_H
#define DATA_H

#include "metadata.h"
#include "aidata.h"

typedef struct {
    MetadataSave* metadata;
    AIDataSave* aidata;
} DataSave;

void initialize_dataSave(DataSave* data,
                     uint16_t input_count,
                     uint16_t output_count,
                     uint64_t num_rules);

void destroy_dataSave(DataSave* data);

#endif