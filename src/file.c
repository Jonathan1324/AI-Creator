#include "file.h"
#include <stdlib.h>

void write_metadata(FILE* file, Metadata *metadata) {
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

int read_metadata(FILE* file, Metadata* metadata) {
    if (!file || !metadata) return 0;

    // Lese das Metadata-Struct (ohne Inputs und Outputs) ein
    size_t read = fread(metadata, sizeof(Metadata) - 2 * sizeof(IOEntry*), 1, file);
    if (read != 1) {
        perror("Error reading Metadata from file");
        return 0;
    }

    // Allokiere Speicher für Inputs und Outputs
    metadata->inputs = malloc(sizeof(IOEntry) * metadata->input_count);
    metadata->outputs = malloc(sizeof(IOEntry) * metadata->output_count);

    if (!metadata->inputs || !metadata->outputs) {
        perror("Error allocating memory for inputs or outputs");
        return 0;
    }

    // Lese die Eingabedaten (inputs)
    read = fread(metadata->inputs, sizeof(IOEntry), metadata->input_count, file);
    if (read != metadata->input_count) {
        perror("Error reading inputs from file");
        return 0;
    }

    // Lese die Ausgabedaten (outputs)
    read = fread(metadata->outputs, sizeof(IOEntry), metadata->output_count, file);
    if (read != metadata->output_count) {
        perror("Error reading outputs from file");
        return 0;
    }

    return 1;
}