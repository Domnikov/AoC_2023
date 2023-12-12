#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL play1(LL T, LL D, LL spd = 0, LL d = 0) {
    if(d > D) {
        P("ret 1: ", T, D, spd, d);
        return 1;
    }
    if(!T) {
        P("Failed: ", T, D, spd, d);
        return 0;
    }
    auto res = 0;
    if(!d) {
        play1(T-1, D, spd+1, d);
    }
    res += play1(T-1, D, spd, d+spd);
    P("Accum: ", T, D, spd, d, res);
    return res;
}

auto count() {
    LL result1 = 0;
    LL result2 = 0;
    auto vecSTime = splitStr(in[0], ' ');
    auto vecSDist = splitStr(in[1], ' ');
    P_VEC(vecSTime);
    P_VEC(vecSDist);
    for(size_t i = 1; i < 2/*vecSTime.size()*/; ++i) {
        auto wins = play1(stoll(vecSTime[i]), stoll(vecSDist[i]));
        P(wins);
        result1 += wins;
    }
    return std::pair<LL,LL> {result1, result2};
}

int main(int argc, char** argv)
{
    auto scores = count();
    P_RR("Part1: %lld\n", scores.first);
    //========================================================

    P_RR("Part2: %lld\n", scores.second);
    return 0;
}
