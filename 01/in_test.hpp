#pragma once
#include "../help_func.hpp"

inline auto getInput()
{
    VECS input {
#if 0
"1abc2",
"pqr3stu8vwx",
"a1b2c3d4e5f",
"treb7uchet",
#else
"two1nine",
"eightwothree",
"abcone2threexyz",
"xtwone3four",
"4nineeightseven2",
"zoneight234",
"7pqrstsixteen",
#endif
    };

    return input;
}
