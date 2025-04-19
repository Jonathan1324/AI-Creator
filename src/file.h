#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdio.h>
#include "metadata.h"

void write_metadata(FILE* file, Metadata *metadata);

int read_metadata(FILE* file, Metadata* metadata);

#endif