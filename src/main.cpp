#include <iostream>
#include <memory>
#include <cstring>

#include "save.hpp"

enum OperatingSystem {
    Windows = 1,
    macOS = 2,
    Linux = 3,
    Unknown = -1
};

int getOperatingSystem() {
    #ifdef _WIN32
        return Windows;
    #elif defined(__APPLE__)
        return macOS;
    #elif defined(__linux__)
        return Linux;
    #else
        return Unknown;
    #endif
}

int main() {
    Data* ai = nullptr;

    while(true) {
        std::cout << "What do you want to do? ";
        if(ai) {
            std::cout << "Current AI: " << ai->metadata->name << std::endl;
        } else {
            std::cout << "No AI loaded currently." << std::endl;
        }
        std::cout << "1. load\n2. save\n3. create\n4. run\n5. quit" << std::endl;

        std::string action;

        std::cin >> action;

        if (action == "1") {

        } else if (action == "2") {

        } else if (action == "3") {

        } else if (action == "4") {

        } else if (action == "5") {
            break;
        } else {
            std::cout << "unknown action" << std::endl;
        }

        std::cout << getOperatingSystem() << std::endl;
    }
    /*
    Data data;

    initializeData(&data);

    strcpy(data.metadata->name, "Test AI Data");
    data.metadata->type = 0;

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
    */

    return 0;
}