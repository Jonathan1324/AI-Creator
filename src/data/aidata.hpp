#ifndef AIDATA_HPP
#define AIDATA_HPP

#include "aidata/ruleset.hpp"
#include <memory>

struct AIData {
    std::shared_ptr<RuleSet> ruleset;
};

#endif