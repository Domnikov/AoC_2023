#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

VECII seeds;

VECI GetInitialSeeds() {
    auto vecS = splitStr(in[0], ' ');

    VECI result;
    for(size_t i = 1; i < vecS.size(); ++i) {
        result.push_back(stoll(vecS[i]));
    }
    return result;
}

size_t FindNext(size_t idx) {
    while(in[++idx].find("map:") == -1){
        if(idx == in.size()-1) {
            return -1;
        }
    }
    return idx;
}

auto count() {
    seeds.push_back(GetInitialSeeds());
    size_t idx = 1;
    while((idx = FindNext(idx)) != -1) {
        P(in[idx]);
        std::map<LL, LL> map;
        while(!in[++idx].empty()){
            auto vec = vecsToVeci(splitStr(in[idx], ' '));
            LL src = vec[1];
            LL dst = vec[0];
            LL sz = vec[2];
            for(LL i = 0; i < sz; ++i) {
                map[src+i] = dst+i;
            }
        }
        VECI new_seeds;
        VECI old_seeds = seeds[seeds.size()-1];
        for(auto s:old_seeds) {
            if(map.count(s)){
                new_seeds.push_back(map[s]);
            } else {
                new_seeds.push_back(s);
            }
        }
        seeds.push_back(new_seeds);
        P_VEC(seeds);
    }
    auto locations = seeds[seeds.size()-1];
    P_VEC(locations);
    LL min = locations[0];
    for(auto n : locations){
        if(min > n) {
            min = n;
        }
    }
    return min;
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
