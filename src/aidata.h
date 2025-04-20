#ifndef AIDATA_H
#define AIDATA_H

#define RULE_BASED 0

#include "aidata/ruleset.h"

#pragma pack(push, 1)       // 1-byte alignment

typedef struct {
    RuleSet* ruleset;
} AIData;

#pragma pack(pop)

void initialize_aidata(AIData* aidata, uint8_t type, uint64_t num_rules);

void destroy_aidata(AIData* aidata, uint8_t type);

#endif