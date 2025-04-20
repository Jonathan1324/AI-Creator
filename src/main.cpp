#include <iostream>

#include "storage/storage.hpp"
#include "data/data.hpp"

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

    DataSave dataSave;

    initialize_dataSave(&dataSave, data.metadata->input_count, data.metadata->output_count, data.aidata->ruleset->rule_count);

    convertDataToSaveData(&dataSave, &data);

    for(int i = 0; i < data.aidata->ruleset->rule_count; i++) {
        dataSave.aidata->ruleset->rules[i].input_id = 0;
        dataSave.aidata->ruleset->rules[i].op = 1;
        dataSave.aidata->ruleset->rules[i].compare_input_id = 1;
        dataSave.aidata->ruleset->rules[i].compare_value = 100;
        dataSave.aidata->ruleset->rules[i].action_type = 0;
        dataSave.aidata->ruleset->rules[i].then_rule_id = 0;
        dataSave.aidata->ruleset->rules[i].else_rule_id = 0;
        dataSave.aidata->ruleset->rules[i].then_output_id = 0;
        dataSave.aidata->ruleset->rules[i].then_output_value = 1;
        dataSave.aidata->ruleset->rules[i].else_output_id = 0;
        dataSave.aidata->ruleset->rules[i].else_output_value = 2;
    }

    writeFile("data.dat", &dataSave);

    destroy_dataSave(&dataSave);

    /*
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
    */

    return 0;
}