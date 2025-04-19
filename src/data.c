#include "data.h"
#include <stdlib.h>

void destroy_data(Data* data) {
    if (!data) return;
    
    destroy_metadata(data->metadata);
}