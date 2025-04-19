#ifndef RULESET_H
#define RULESET_H

#include <stdint.h>

#pragma pack(push, 1)       // 1-byte alignment

// 48 bytes
typedef struct {
    uint16_t input_id;
    uint8_t op;
    uint64_t compare_value;

    uint8_t action_type;
//  0: then rule,   else rule
//  1: then action, else rule
//  2: then rule,   else action
//  3: then action, else action

    uint64_t then_rule_id;
    uint64_t else_rule_id;

    uint16_t then_output_id;
    uint64_t then_output_value;

    uint16_t else_output_id;
    uint64_t else_output_value;
} Rule;

typedef struct {
    uint64_t rule_count;
    uint64_t rule_rule_id;
    Rule* rules;
} RuleSet;

#pragma pack(pop)

#endif