#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

bool IsStable(const VECI& vec) {
    LL n = vec[0];
    for(const auto& v: vec) {
        if(n != v) {
            return false;
        }
    }
    return true;
}

LL CountOne1(VECI& vec){
    P_VEC(vec);
    if(IsStable(vec)){
        return vec[0];
    }
    VECI next_level;
    for(LL i = 1; i < vec.size(); ++i) {
        next_level.push_back(vec[i] - vec[i-1]);
    }
    return vec[vec.size()-1] + CountOne1(next_level);
}

auto count1() {
    LL result = 0;
    for(const auto& s : in){
        auto vec = vecsToVeci(splitStr(s, ' '));
        LL n = CountOne1(vec);
        result += n;
    }
    return result;
}

LL CountOne2(VECI& vec){
    P_VEC(vec);
    if(IsStable(vec)){
        return vec[0];
    }
    VECI next_level;
    for(LL i = 1; i < vec.size(); ++i) {
        next_level.push_back(vec[i] - vec[i-1]);
    }
    return vec[0] - CountOne2(next_level);
}

auto count2() {
    LL result = 0;
    for(const auto& s : in){
        auto vec = vecsToVeci(splitStr(s, ' '));
        LL n = CountOne2(vec);
        result += n;
    }
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
