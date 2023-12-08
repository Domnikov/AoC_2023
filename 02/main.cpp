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
        auto l = splitStr(s, ':');
        auto l1 = splitStr(l[0], ' ');
        P("Game: ", l1[1]);
        auto l2 = splitStr(l[1], ',');
        std::map<S, LL> balls;
        for(auto set: l2){
            auto l3 = splitStr(set, ' ');
            auto num = stoi(l3[0]);
            auto color = l3[1];
            if(!balls.count(color)){
                balls[color] = 0;
            }
            balls[color] += num;
            P(l3[0], l3[1]);
        }

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
