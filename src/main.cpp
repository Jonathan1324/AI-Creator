#include <iostream>
#include <memory>
#include <cstring>

#include "save.hpp"
#include "cli/cli.hpp"

int main() {
    Data* ai = nullptr;

    std::string msg = "";
    std::vector<AEC> aecs;

    clear();

    while(true) {
        if(msg != "") {
            printText(msg, aecs);
        }
        msg = "";
        aecs.clear();

        if(ai) {
            printText(std::string("What do you want to do? ") + "Current AI: " + ai->metadata->name);
        } else {
            printText("What do you want to do? No AI loaded currently.");
        }
        printText("1. load");
        printText("2. save");
        printText(ai ? "3. change" : "3. create");
        printText("4. run");
        printText("5. quit");

        std::string action;

        std::getline(std::cin, action);

        if (action == "1") {
            /*
            clear();

            ai = new Data();
            initializeData(ai);

            std::string file;
            
            printText("Load from file", {green});
            printText("What's the name of the file? ");
            std::getline(std::cin, file);

            const int status = loadData(ai, file.c_str());

            switch (status) {
                case 1:
                    aecs.push_back(red);
                    msg = "Error opening file for reading.";
                    break;
                case 2:
                    aecs.push_back(red);
                    msg = "Error reading metadata from file.";
                    break;
                case 3:
                    aecs.push_back(red);
                    msg = "Error reading aidata from file.";
                    break;
            }
            */
        } else if (action == "2") {
            clear();

            if(!ai) {
                aecs.push_back(red);
                msg = "No ai loaded.";
            } else {
                std::string file;

                printText("Save to file", {green});
                printText("What's the name of the file? ");
                std::getline(std::cin, file);

                const int status = saveData(ai, file.c_str());

                switch (status) {
                    case 1:
                        aecs.push_back(red);
                        msg = "Error saving to file";
                        break;
                }
            }
        } else if (action == "3") {
            clear();

            ai = new Data();
            initializeData(ai);
            ai->metadata->type = 0;

            ai->aidata->ruleset->rule_count = 0;

            std::string name;

            printText("What should it be called (max. 255 letters)? ");
            std::getline(std::cin, name);

            if(name.length() > 255) {
                delete ai;
                ai = nullptr;
                aecs.push_back(red);
                msg = "name is too long.";
            } else {
                std::strcpy(ai->metadata->name, name.c_str());
            }
        } else if (action == "4") {

        } else if (action == "5") {
            break;
        } else {
            aecs.push_back(red);
            msg = "unknown action";
        }

        clear();
    }
    if (ai) {
        delete ai;
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