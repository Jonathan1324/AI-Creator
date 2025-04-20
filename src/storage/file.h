#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdio.h>
#include "data.h"

void write_metadata(FILE* file, MetadataSave *metadata);

int read_metadata(FILE* file, MetadataSave* metadata);

int readFile(const char* filename, DataSave* data);
int writeFile(const char* filename, DataSave* data);

void write_ruleset(FILE* file, RuleSetSave *ruleset);
void read_ruleset(FILE* file, RuleSetSave *ruleset);

#endif