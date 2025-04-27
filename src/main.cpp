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

int clear() {
    const int os = getOperatingSystem();

    switch(os) {
        case Windows:
            system("cls");
            return 1;
        case macOS:
        case Linux:
            system("clear");
            return 1;
        case Unknown:
            system("clear");
            return -1;
    }

    return -1;
}

int main() {
    Data* ai = nullptr;

    std::string msg = "";
    std::string aecs = "";

    clear();

    while(true) {
        if(msg != "") {
            std::cout << aecs << msg << "\033[0m" << std::endl;
        }
        msg = "";
        aecs = "";

        std::cout << "What do you want to do? ";
        if(ai && ai->metadata) {
            std::cout << "Current AI: " << ai->metadata->name << std::endl;
        } else {
            std::cout << "No AI loaded currently." << std::endl;
        }
        std::cout << "1. load\n2. save\n3. " << (ai == nullptr ? "create" : "change") << "\n4. run\n5. quit" << std::endl;

        std::string action;

        std::getline(std::cin, action);

        if (action == "1") {
            std::string file;
            
            std::getline(std::cin, file);

            const int status = loadData(ai, file.c_str());

            switch (status) {
                case 1:
                    aecs = "\033[31m";
                    msg = "Error opening file for reading.";
                    break;
                case 2:
                    aecs = "\033[31m";
                    msg = "Error reading metadata from file.";
                    break;
                case 3:
                    aecs = "\033[31m";
                    msg = "Error reading aidata from file.";
                    break;
            }
        } else if (action == "2") {

        } else if (action == "3") {
            
        } else if (action == "4") {

        } else if (action == "5") {
            break;
        } else {
            aecs = "\033[31m";
            msg = "unknown action";
        }

        clear();
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