#ifndef COLORS_HPP
#define COLORS_HPP

enum AEC {
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    magenta = 5,
    cyan = 6,
    white = 7
};

const char* getAECCode(AEC color);

#endif