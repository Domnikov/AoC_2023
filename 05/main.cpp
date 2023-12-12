#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

VECII map;

VECI GetInitialSeeds() {
    auto vecS = splitStr(in[0], ' ');

    VECI result;
    for(size_t i = 1; i < vecS.size(); ++i) {
        result.push_back(stoll(vecS[i]));
    }
    return result;
}

auto count() {
    LL result = 0;
    map.push_back(GetInitialSeeds());

    P_VECV(map);
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
