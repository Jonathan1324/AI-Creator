#include <iostream>

extern "C" {
    #include "storage/storage.h"
}

int main() {
    DataSave data;

    initialize_dataSave(&data, 1, 1, 1);

    
    strcpy(data.metadata->name, "Test Metadata");
    data.metadata->type = RULE_BASED;

    strcpy(data.metadata->inputs[0].name, "Input 1");
    data.metadata->inputs[0].id = 0;

    strcpy(data.metadata->inputs[1].name, "Input 2");
    data.metadata->inputs[1].id = 1;

    strcpy(data.metadata->outputs[0].name, "Output 1");
    data.metadata->outputs[0].id = 0;


    data.aidata->ruleset->rules[0].input_id = 0;
    data.aidata->ruleset->rules[0].op = 1;
    data.aidata->ruleset->rules[0].compare_input_id = 1;
    data.aidata->ruleset->rules[0].compare_value = 100;
    data.aidata->ruleset->rules[0].action_type = 0;
    data.aidata->ruleset->rules[0].then_rule_id = 0;
    data.aidata->ruleset->rules[0].else_rule_id = 0;
    data.aidata->ruleset->rules[0].then_output_id = 0;
    data.aidata->ruleset->rules[0].then_output_value = 1;
    data.aidata->ruleset->rules[0].else_output_id = 0;
    data.aidata->ruleset->rules[0].else_output_value = 2;


    writeFile("data.dat", &data);

    destroy_dataSave(&data);

    return 0;
}