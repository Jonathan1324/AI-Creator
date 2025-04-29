#include "data.hpp"
#include <stack>
#include <unordered_map>
#include <iostream>

void initializeData(Data* data) {
    data->exists = true;

    std::shared_ptr<Metadata> metadata = std::make_shared<Metadata>();
    data->metadata = metadata;

    strcpy(metadata->name, "");
    metadata->type = 0;

    metadata->input_count = 0;
    metadata->output_count = 0;

    std::shared_ptr<AIData> aidata = std::make_shared<AIData>();

    aidata->ruleset = nullptr;

    switch (metadata->type) {
        case RULE_BASED:
            aidata->ruleset = std::make_shared<RuleSet>();
            break;
        default:
            break;
    }

    data->aidata = aidata;
}

void convertMetadataToMetadataSave(DataSave* dataSave, Data* data) {
    memset(dataSave->metadata->name, 0, 255);
    strncpy(dataSave->metadata->name, data->metadata->name, std::min(std::strlen(data->metadata->name), sizeof(dataSave->metadata->name)));
    dataSave->metadata->type = data->metadata->type;

    for(int i = 0; i < data->metadata->input_count; i++) {
        memset(dataSave->metadata->inputs[i].name, 0, 255);
        strncpy(dataSave->metadata->inputs[i].name, data->metadata->inputs.at(i).name, std::min(std::strlen(data->metadata->inputs.at(i).name), sizeof(dataSave->metadata->inputs[i].name)));
        dataSave->metadata->inputs[i].id = data->metadata->inputs.at(i).id;
    }

    for(int i = 0; i < data->metadata->output_count; i++) {
        memset(dataSave->metadata->outputs[i].name, 0, 255);
        strncpy(dataSave->metadata->outputs[i].name, data->metadata->outputs.at(i).name, std::min(std::strlen(data->metadata->outputs.at(i).name), sizeof(dataSave->metadata->outputs[i].name)));
        dataSave->metadata->outputs[i].id = data->metadata->outputs.at(i).id;
    }
}

std::vector<std::shared_ptr<Rule>> collectAllRules(std::shared_ptr<Rule>& root_rule) {
    std::stack<std::shared_ptr<Rule>> stack;
    std::vector<std::shared_ptr<Rule>> rules;

    stack.push(root_rule);

    while (!stack.empty()) {
        std::shared_ptr<Rule> current = stack.top();
        stack.pop();

        if (!current) continue;

        rules.push_back(current);

        if (current->action_type == 0 || current->action_type == 2 ||
            current->action_type == 4 || current->action_type == 6) {
            if (current->then_rule) stack.push(current->then_rule);
        }

        if (current->action_type == 0 || current->action_type == 1 ||
            current->action_type == 4 || current->action_type == 5) {
            if (current->else_rule) stack.push(current->else_rule);
        }
    }

    return rules;
}

void convertAIDataToAIDataSave(DataSave* dataSave, Data* data) {
    std::vector<std::shared_ptr<Rule>> all_rules = collectAllRules(data->aidata->ruleset->root_rule);
    std::unordered_map<const Rule*, uint64_t> rule_to_id;

    for (size_t i = 0; i < all_rules.size(); ++i) {
        rule_to_id[all_rules[i].get()] = i;
    }

    RuleSave* rule_saves = new RuleSave[all_rules.size()];

    for (size_t i = 0; i < all_rules.size(); ++i) {
        const std::shared_ptr<Rule>& rule = all_rules[i];
        RuleSave& rs = rule_saves[i];

        rs.input_id = rule->input_id;
        rs.op = rule->op;
        rs.compare_input_id = rule->compare_input_id;
        rs.compare_value = rule->compare_value;
        rs.action_type = rule->action_type;

        rs.then_rule_id = UINT64_MAX;
        rs.else_rule_id = UINT64_MAX;

        if ((rule->action_type & 0b0001) == 0 && rule->then_rule) { // THEN ist Rule
            rs.then_rule_id = rule_to_id[rule->then_rule.get()];
        }
        if ((rule->action_type & 0b0010) == 0 && rule->else_rule) { // ELSE ist Rule
            rs.else_rule_id = rule_to_id[rule->else_rule.get()];
        }

        rs.then_output_id = rule->then_output_id;
        rs.then_output_value = rule->then_output_value;
        rs.else_output_id = rule->else_output_id;
        rs.else_output_value = rule->else_output_value;
    }

    uint64_t root_id = data->aidata->ruleset->root_rule ? rule_to_id[data->aidata->ruleset->root_rule.get()] : UINT64_MAX;

    dataSave->aidata->ruleset->rule_count = all_rules.size();
    dataSave->aidata->ruleset->root_rule_id = root_id;
    dataSave->aidata->ruleset->rules = rule_saves;
}


void convertMetadataSaveToMetadata(DataSave* dataSave, Data* data) {
    std::strncpy(data->metadata->name, dataSave->metadata->name, sizeof(data->metadata->name) - 1);
    data->metadata->name[sizeof(data->metadata->name) - 1] = '\0';

    data->metadata->type = dataSave->metadata->type;

    data->metadata->inputs.clear();
    data->metadata->outputs.clear();
    
    for (int i = 0; i < dataSave->metadata->input_count; ++i) {
        uint16_t id = dataSave->metadata->inputs[i].id;
        const char* name = dataSave->metadata->inputs[i].name;

        data->metadata->addInput(id, name);
    }

    for (int i = 0; i < dataSave->metadata->output_count; ++i) {
        uint16_t id = dataSave->metadata->outputs[i].id;
        const char* name = dataSave->metadata->outputs[i].name;

        data->metadata->addOutput(id, name);
    }
}

void convertRuleSavetoRule(RuleSave* ruleSave, std::shared_ptr<Rule> rule) {
    rule->input_id = ruleSave->input_id;
    rule->op = ruleSave->op;
    rule->compare_input_id = ruleSave->compare_input_id;
    rule->compare_value = ruleSave->compare_value;
    
    rule->action_type = ruleSave->action_type;

    rule->then_output_id = ruleSave->then_output_id;
    rule->then_output_value = ruleSave->then_output_value;

    rule->else_output_id = ruleSave->else_output_id;
    rule->else_output_value = ruleSave->else_output_value;
}

std::shared_ptr<Rule> buildRuleFromSave(
    RuleSave* rules,
    uint64_t rule_id,
    std::unordered_map<uint64_t, std::shared_ptr<Rule>>& created_rules
) {
    if (created_rules.count(rule_id)) {
        return created_rules[rule_id];
    }

    RuleSave* ruleSave = &rules[rule_id];
    std::shared_ptr<Rule> rule = std::make_shared<Rule>();

    convertRuleSavetoRule(ruleSave, rule);
    created_rules[rule_id] = rule;

    if (ruleSave->then_rule_id != UINT64_MAX) {
        rule->then_rule = buildRuleFromSave(rules, ruleSave->then_rule_id, created_rules);
    } else {
        rule->then_rule = nullptr;
    }

    if (ruleSave->else_rule_id != UINT64_MAX) {
        rule->else_rule = buildRuleFromSave(rules, ruleSave->else_rule_id, created_rules);
    } else {
        rule->else_rule = nullptr;
    }

    return rule;
}

void convertAIDataSaveToAIData(DataSave* dataSave, Data* data) {
    data->aidata->ruleset->rule_count = dataSave->aidata->ruleset->rule_count;

    std::unordered_map<uint64_t, std::shared_ptr<Rule>> created_rules;

    uint64_t root_id = dataSave->aidata->ruleset->root_rule_id;
    RuleSave* rules = dataSave->aidata->ruleset->rules;

    std::shared_ptr<Rule> root_rule = buildRuleFromSave(rules, root_id, created_rules);

    data->aidata->ruleset->root_rule = root_rule;
}