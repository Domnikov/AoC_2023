#pragma once
#include "../help_func.hpp"

inline auto getInput()
{
    VECS input {
"broadcaster -> a, b, c",
"%a -> b",
"%b -> c",
"%c -> inv",
"&inv -> a",
    };

    return input;
}
