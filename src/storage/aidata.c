#include "aidata.h"
#include <stdlib.h>

void initialize_aidata(AIDataSave* aidata, uint8_t type, uint64_t num_rules) {
    if (!aidata) return;

    switch(type) {
        case RULE_BASED:
            aidata->ruleset = (RuleSetSave*)malloc(sizeof(RuleSetSave));
            initialize_ruleset(aidata->ruleset, num_rules);
    }
}

void destroy_aidata(AIDataSave* aidata, uint8_t type) {
    if (!aidata) return;

    switch(type) {
        case RULE_BASED:
            destroy_ruleset(aidata->ruleset);
            free(aidata->ruleset);
            break;
    }
}