#pragma once
#include "../help_func.hpp"

inline auto getInput()
{
    VECS input {
"LLR",
"",
"AAA = (BBB, BBB)",
"BBB = (AAA, ZZZ)",
"ZZZ = (ZZZ, ZZZ)",
    };

    return input;
}
