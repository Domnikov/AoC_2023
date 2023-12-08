#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

auto count() {
    LL result = 0;
    for(auto s : in){
        auto card = stoi(splitStr(splitStr(s,':')[0], ' ')[1]);
        auto swins = splitStr(splitStr(splitStr(s, ':')[1], '|')[0], ' ');
        auto smy = splitStr(splitStr(splitStr(s, ':')[1], '|')[1], ' ');
        VECI wins, my;
        VECSTOA(swins, wins);
        VECSTOA(smy, my);
        P_VEC(wins);
        P_VEC(my);

    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================
return 0;
    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
