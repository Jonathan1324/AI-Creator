#include "file.h"
#include <stdio.h>

void write_metadata(const char *filename, Metadata *metadata) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    size_t written = fwrite(metadata, sizeof(Metadata) - 2 * sizeof(IOEntry*), 1, file);
    if (written != 1) {
        perror("Error writing Metadata to file");
        return;
    }


    // Write the inputs and outputs

    written = fwrite(metadata->inputs, sizeof(IOEntry), metadata->input_count, file);
    if (written != metadata->input_count) {
        perror("Error writing inputs to file");
        return;
    }

    written = fwrite(metadata->outputs, sizeof(IOEntry), metadata->output_count, file);
    if (written != metadata->output_count) {
        perror("Error writing outputs to file");
        return;
    }

    fclose(file);
}