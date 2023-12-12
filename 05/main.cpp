#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

using VECPLL = std::vector<std::pair<LL,LL>>;

VECPLL GetInitialSeeds1() {
    auto vecS = splitStr(in[0], ' ');

    VECPLL result;
    for(size_t i = 1; i < vecS.size(); ++i) {
        auto num = stoll(vecS[i]);
        result.push_back({num, num});
    }
    return result;
}

VECPLL GetInitialSeeds2() {
    auto seeds1 = GetInitialSeeds1();
    return seeds1;
    // VECI seeds2;
    // for(size_t i = 0; i < seeds1.size()/2; ++i){
    //     for(LL j = 0; j < seeds1[i*2+1]; ++j){
    //         seeds2.push_back(seeds1[i*2]+j);
    //     }
    //     P(i);
    // }
    //
    // return seeds2;
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

std::pair<VECPLL, VECPLL> GetCross(std::pair<LL, LL>& seed, LL src, LL dst, LL sz) {
    auto src_a = seed.first;
    auto src_b = seed.second;
    seed = {0,0};

    if(src_b < src || src_a > src+sz) {
        return {VECPLL{}, VECPLL{{src_a, src_b}}};
    }
    std::pair<LL,LL> cuted {std::max(src_a, src), std::min(src_b, src+sz)};
    VECPLL orig;
    if(cuted.second < src_b) {
        orig .push_back({cuted.second+1, src_b});
    }
    if(cuted.first > src_a) {
        orig .push_back({src, cuted.first-1});
    }
    return {VECPLL{{cuted.first - src + dst, cuted.second-src+dst}}, orig};
}

auto count(VECPLL seeds) {
    size_t idx = 1;
    while((idx = FindNext(idx)) != -1) {
        P(in[idx]);
        VECPLL converted;
        while(!in[++idx].empty()){
            auto vec = vecsToVeci(splitStr(in[idx], ' '));
            LL src = vec[1];
            LL dst = vec[0];
            LL sz = vec[2];
            for(auto& s:seeds) {
                auto new_diaposons = GetCross(s, src, dst, sz);
                for(auto d : new_diaposons.second) {
                    P("orig", d.first, d.second);
                    seeds.push_back(d);
                }
                for(auto d : new_diaposons.first) {
                    P("new", d.first, d.second);
                    converted.push_back(d);
                }
            }
        }
        for(auto& s:seeds) {
            converted.push_back(s);
        }
        seeds = converted;
    }
    LL min = seeds[0].first;
    for(auto n : seeds){
        if(min > n.first) {
            min = n.first;
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
