#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include "metadata.h"

void write_metadata(const char *filename, Metadata *metadata);

#endif