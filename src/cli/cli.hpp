#ifndef CLI_HPP
#define CLI_HPP

extern "C" {
    #include "cli.h"
}
#include <iostream>
#include <vector>
#include "colors.hpp"

int printText(std::string text, std::vector<AEC> AECs = {}, bool centered = false, bool newLine = true);

#endif