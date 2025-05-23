#include "colors.hpp"

const char* getAECCode(AEC color) {
    switch (color) {
        case black: return "\033[30m";
        case red: return "\033[31m";
        case green: return "\033[32m";
        case yellow: return "\033[33m";
        case blue: return "\033[34m";
        case magenta: return "\033[35m";
        case cyan: return "\033[36m";
        case white: return "\033[37m";
        default: return "\033[0m";
    }
}