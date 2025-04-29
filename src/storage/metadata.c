#include "metadata.h"
#include <stdlib.h>
#include <string.h>

int initialize_metadata(MetadataSave* meta, uint16_t input_count, uint16_t output_count) {
    if (!meta) return 0;

    strcpy(meta->magic, "AI C");
    meta->version = 1;

    memset(meta->name, 0, 255); // Initialize name to empty
    meta->type = 0;
    meta->input_count = input_count;
    meta->output_count = output_count;

    meta->inputs = malloc(sizeof(IOEntrySave) * input_count);
    meta->outputs = malloc(sizeof(IOEntrySave) * output_count);

    if (!meta->inputs || !meta->outputs) {
        free(meta->inputs);
        free(meta->outputs);
        meta->inputs = NULL;
        meta->outputs = NULL;
        return 0; // Fehler
    }

    return 1; // Erfolg
}

void destroy_metadata(MetadataSave* meta) {
    if (!meta) return;
    free(meta->inputs);
    free(meta->outputs);
}
