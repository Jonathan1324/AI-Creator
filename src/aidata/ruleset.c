#include "ruleset.h"
#include <stdlib.h>
#include <string.h>

void initialize_ruleset(RuleSet* ruleset, int num_rules) {
    if (!ruleset || num_rules <= 0) {
        return;
    }

    ruleset->rule_count = (uint64_t)num_rules;
    ruleset->root_rule_id = 0;  // Standardmäßig auf 0 setzen oder ggf. einen Initialwert vergeben

    ruleset->rules = (Rule*)malloc(sizeof(Rule) * num_rules);
    if (!ruleset->rules) {
        ruleset->rule_count = 0;
        return;
    }

    // Optional: Speicher auf 0 setzen
    memset(ruleset->rules, 0, sizeof(Rule) * num_rules);
}

void destroy_ruleset(RuleSet* ruleset) {
    if(!ruleset) {
        return;
    }

    if(ruleset->rules) {
        free(ruleset->rules);
        ruleset->rules = NULL;
    }
}