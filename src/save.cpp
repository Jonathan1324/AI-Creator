#include "save.hpp"

void saveData(Data* data, char* filename) {
    DataSave dataSave;

    initialize_dataSave(&dataSave, data->metadata->input_count, data->metadata->output_count, data->aidata->ruleset->rule_count);

    convertDataToSaveData(&dataSave, data);

    for(int i = 0; i < data->aidata->ruleset->rule_count; i++) {
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

    writeFile(filename, &dataSave);

    destroy_dataSave(&dataSave);
}