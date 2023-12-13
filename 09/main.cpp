#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL CountOne(VECI vec){
    P_VEC(vec);
    return 0;
}

auto count() {
    LL result = 0;
    for(const auto& s : in){
        auto vec = vecsToVeci(splitStr(s, ' '));
        CountOne(vec);
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
