#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL play1(LL T, LL D, LL spd = 0) {
    auto res = 0;
    while(T) {
        // P(T, spd, D, T*spd);
        if(T*spd > D) {
            res += 1;
        }
        --T;
        ++spd;
    }
    return res;
}

auto count() {
    LL result1 = 1;
    LL result2 = 0;
    auto vecSTime = splitStr(in[0], ' ');
    auto vecSDist = splitStr(in[1], ' ');
    // for(size_t i = 1; i < 2; ++i) {
    for(size_t i = 1; i < vecSTime.size(); ++i) {
        auto wins = play1(stoll(vecSTime[i]), stoll(vecSDist[i]));
        result1 *= wins;
    }
    S time2;
    S dist2;
    for(size_t i = 1; i < vecSTime.size(); ++i) {
        time2 += vecSTime[i];
        dist2 += vecSDist[i];
    }
    auto t2 = stoll(time2);
    auto d2 = stoll(dist2);
    result2 = play1(t2, d2);

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
