#ifndef DATA_H
#define DATA_H

#include "metadata.h"
#include "aidata.h"

typedef struct {
    Metadata* metadata;
    AIData* aidata;
} Data;

void destroy_data(Data* data);

#endif