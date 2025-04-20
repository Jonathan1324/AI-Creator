#ifndef AIDATA_H
#define AIDATA_H

#define RULE_BASED 0

#include "aidata/ruleset.h"

#pragma pack(push, 1)       // 1-byte alignment

typedef struct {
    RuleSetSave* ruleset;
} AIDataSave;

#pragma pack(pop)

void initialize_aidata(AIDataSave* aidata, uint8_t type, uint64_t num_rules);

void destroy_aidata(AIDataSave* aidata, uint8_t type);

#endif