#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

VECI GetInitialSeeds1() {
    auto vecS = splitStr(in[0], ' ');

    VECI result;
    for(size_t i = 1; i < vecS.size(); ++i) {
        result.push_back(stoll(vecS[i]));
    }
    return result;
}

VECI GetInitialSeeds2() {
    auto seeds1 = GetInitialSeeds1();
    VECI seeds2;
    for(size_t i = 0; i < seeds1.size()/2; ++i){
        for(LL j = 0; j < seeds1[i*2+1]; ++j){
            seeds2.push_back(seeds1[i*2]+j);
        }
    }

    return seeds2;
}

size_t FindNext(size_t idx) {
    if(idx == in.size()-1) {
        return -1;
    }
    while(in[++idx].find("map:") == -1){
        if(idx == in.size()-1) {
            return -1;
        }
    }
    return idx;
}

auto count(VECI seeds) {
    size_t idx = 1;
    while((idx = FindNext(idx)) != -1) {
        P(in[idx]);
        while(!in[++idx].empty()){
            auto vec = vecsToVeci(splitStr(in[idx], ' '));
            LL src = vec[1];
            LL dst = vec[0];
            LL sz = vec[2];
            for(auto& s:seeds) {
                if(s >= src && s <= src+sz){
                    s = dst + s - src;
                    s *= -1;
                }
            }
        }
        for(auto& s:seeds) {
            if(s < 0) {
                s *= -1;
            }
        }
    }
    LL min = seeds[0];
    for(auto n : seeds){
        if(min > n) {
            min = n;
        }
    }
    return min;
}

int main(int argc, char** argv) {
    LL score = 0;
    auto seeds1 = GetInitialSeeds1();
    score = count(seeds1);
    P_RR("Part1: %lld\n", score);
    //========================================================

    auto seeds2 = GetInitialSeeds2();
    score = count(seeds2);
    P_RR("Part2: %lld\n", score);
    return 0;
}
