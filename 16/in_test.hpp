#pragma once
#include "../help_func.hpp"

inline auto getInput()
{
    VECS input {
R"(.|...\....)",
R"(|.-.\.....)",
R"(.....|-...)",
R"(........|.)",
R"(..........)",
R"(.........\)",
R"(..../.\\..)",
R"(.-.-/..|..)",
R"(.|....-|.\)",
R"(..//.|....)",
    };

    return input;
}
