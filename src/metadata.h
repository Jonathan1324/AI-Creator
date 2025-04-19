#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>

#pragma pack(push, 1)       // 1-byte alignment

typedef struct {
    uint16_t id;            // 2 bytes for the ID
    char name[254];         // 254 bytes for the name
} IOEntry;

typedef struct {
    char name[255];         // 255 bytes for the name
    uint8_t type;           // 1 byte for the type

    uint16_t input_count;   // 2 bytes for the number of inputs
    uint16_t output_count;  // 2 bytes for the number of outputs

    IOEntry* inputs;        // Pointer to an array of IOEntry for inputs
    IOEntry* outputs;       // Pointer to an array of IOEntry for outputs
} Metadata;

#pragma pack(pop)

int initialize_metadata(Metadata* meta, uint16_t input_count, uint16_t output_count);

void destroy_metadata(Metadata* meta);

#endif