#include "cli.hpp"

int printText(std::string text, std::vector<AEC> AECs, bool centered, bool newLine) {
    std::string aecs = "";

    for(long long unsigned int i = 0; i < AECs.size(); i++) {
        aecs += getAECCode(AECs.at(i));
    }

    std::string string = aecs + text + "\033[0m" + (newLine ? "\n" : "");

    if (centered) {
        printCentered(string.c_str());
    } else {
        print(string.c_str());
    }

    return 0;
}