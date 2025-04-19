#ifndef AIDATA_H
#define AIDATA_H

#include "aidata/ruleset.h"

#pragma pack(push, 1)       // 1-byte alignment

typedef struct {
    RuleSet* ruleset;
} AIData;

#pragma pack(pop)

#endif