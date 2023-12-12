#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL play (LL t, LL d) {
    return 10;
}

auto count() {
    LL result = 0;
    auto vecSTime = splitStr(in[0], ' ');
    auto vecSDist = splitStr(in[1], ' ');
    P_VEC(vecSTime);
    P_VEC(vecSDist);
    for(size_t i = 1; i < vecSTime.size(); ++i) {
        result += play(stoll(vecSTime[i]), stoll(vecSDist[i]));
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
