#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();
std::map<S, VECS> ffmod;
std::map<S, VECS> cjmod;

auto count1() {
    LL result = 0;

    return result;
}

auto count2() {
    LL result = 0;

    return result;
}

int main(int argc, char** argv)
{
    for(const auto& l: in){
        auto v = splitStr(l, '>');
        auto name = splitStr(v[0], ' ')[0];
        auto outs = splitStr(v[1], ',');
        char type = name[0];
        name.erase(0,1);
        if(type == '%') {
            ffmod[name] = outs;
        } else if(type == '&') {
            cjmod[name] = outs;
        } else {
            P(type);
            P_LINE;
            exit(1);
        }
    }

    P_MAP(ffmod);
    P_MAP(cjmod);


    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
