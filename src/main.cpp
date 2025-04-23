#include <iostream>

#include "save.hpp"

int main() {
    Data data;

    initializeData(&data);

    strcpy(data.metadata->name, "Test AI Data");
    data.metadata->type = 0;

    data.metadata->input_count = 0;
    data.metadata->output_count = 0;

    data.metadata->addInput(0, "Input 1");
    data.metadata->addInput(1, "Input 2");
    data.metadata->addOutput(0, "Output 1");


    data.aidata->ruleset->rule_count = 1;

    std::shared_ptr<Rule> root_rule = std::make_shared<Rule>();

    root_rule->input_id = 0;
    root_rule->op = 1;
    root_rule->compare_input_id = 1;
    root_rule->compare_value = 100;
    root_rule->action_type = 3;
    root_rule->then_rule = nullptr;
    root_rule->else_rule = nullptr;
    root_rule->then_output_id = 0;
    root_rule->then_output_value = 1;
    root_rule->else_output_id = 0;
    root_rule->else_output_value = 2;
    
    data.aidata->ruleset->root_rule = root_rule;

    saveData(&data, "data.dat");

    Data d;

    initializeData(&d);

    loadData(&d, "data.dat");

    return 0;
}