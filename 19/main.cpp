#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

auto count1() {
    LL result = 0;
    std::map<S, VECSS> map;
    for(const auto& s:in){
        if(s.empty()) break;

        auto v1 = splitStr(s, '{');
        S name = v1[0];
        VECSS cond;
        v1[1].erase(v1[1].size()-1);
        P(v1);
        auto v2 = splitStr(v1[1], ',');
        P(v2);
        for(auto vs:v2){
            auto v3 = splitStr(vs,':');
        P(v3);
            cond.push_back(v3);
        }
        map[name] = cond;
    }

    P_MAPV(map);

    return result;
}

auto count2() {
    LL result = 0;

    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
