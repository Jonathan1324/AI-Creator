#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdio.h>
#include "data.h"

void write_metadata(FILE* file, Metadata *metadata);

int read_metadata(FILE* file, Metadata* metadata);

int readFile(const char* filename, Data* data);
int writeFile(const char* filename, Data* data);

void write_ruleset(FILE* file, RuleSet *ruleset);
void read_ruleset(FILE* file, RuleSet *ruleset);

#endif