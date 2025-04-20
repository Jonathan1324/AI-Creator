#ifndef RULESET_H
#define RULESET_H

#include <stdint.h>

#pragma pack(push, 1)       // 1-byte alignment

// 50 bytes
typedef struct {
    uint16_t input_id;
    uint8_t op;
    uint16_t compare_input_id;
    uint64_t compare_value;

    uint8_t action_type;
//  0: then rule,   else rule,      compare to value
//  1: then action, else rule,      compare to value
//  2: then rule,   else action,    compare to value
//  3: then action, else action,    compare to value
//  4: then rule,   else rule,      compare to input
//  5: then action, else rule,      compare to input
//  6: then rule,   else action,    compare to input
//  7: then action, else action,    compare to input

    uint64_t then_rule_id;
    uint64_t else_rule_id;

    uint16_t then_output_id;
    uint64_t then_output_value;

    uint16_t else_output_id;
    uint64_t else_output_value;
} Rule;

typedef struct {
    uint64_t rule_count;
    uint64_t root_rule_id;
    Rule* rules;
} RuleSet;

#pragma pack(pop)

void initialize_ruleset(RuleSet* ruleset, int num_rules);

void destroy_ruleset(RuleSet* ruleset);

#endif