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
    VECPLL seeds2;
    for(size_t i = 0; i < seeds1.size()/2; ++i){
        seeds2.push_back({seeds1[i*2].first, seeds1[i*2].first + seeds1[i*2+1].first - 1});
        // P(seeds2.back());
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

std::pair<VECPLL, VECPLL> GetCross(std::pair<LL, LL>& seed, LL src, LL dst, LL sz) {
    P(seed);
    auto src_a = seed.first;
    auto src_b = seed.second;
    seed = {0,0};

    if(src_b < src || src_a > src+sz) {
        P(src_b, "<", src, "||", src_a, ">", src+sz);
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
        P_RR("\n");
        P(in[idx]);
        VECPLL converted;
        while(!in[++idx].empty()){
            auto vec = vecsToVeci(splitStr(in[idx], ' '));
            LL src = vec[1];
            LL dst = vec[0];
            LL sz = vec[2];
            P(src, dst,sz);
            VECPLL new_seeds;
            for(auto& s:seeds) {
                auto new_diaposons = GetCross(s, src, dst, sz);
                P_VEC(new_diaposons.first);
                P_VEC(new_diaposons.second);
                for(auto d : new_diaposons.second) {
                    new_seeds.push_back(d);
                }
                for(auto d : new_diaposons.first) {
                    converted.push_back(d);
                }
            }
            seeds = new_seeds;
            P_VEC(seeds);
            P_VEC(converted);
        }
        P_VEC(seeds);
        P_VEC(converted);
        for(auto& s:seeds) {
            converted.push_back(s);
        }
        seeds = converted;
        P_VEC(seeds);
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
    // auto seeds1 = GetInitialSeeds1();
    VECPLL seeds1;
    seeds1.push_back({79, 79});
    seeds1.push_back({80, 80});
    seeds1.push_back({81, 81});
    seeds1.push_back({82, 82});
    seeds1.push_back({83, 83});
    seeds1.push_back({84, 84});
    seeds1.push_back({85, 85});
    seeds1.push_back({86, 86});
    seeds1.push_back({87, 87});
    seeds1.push_back({88, 88});
    seeds1.push_back({89, 89});
    seeds1.push_back({90, 90});
    seeds1.push_back({91, 91});
    seeds1.push_back({92, 92});
    seeds1.push_back({55, 55});
    seeds1.push_back({56, 56});
    seeds1.push_back({57, 57});
    seeds1.push_back({58, 58});
    seeds1.push_back({59, 59});
    seeds1.push_back({60, 60});
    seeds1.push_back({61, 61});
    seeds1.push_back({62, 62});
    seeds1.push_back({63, 63});
    seeds1.push_back({64, 64});
    seeds1.push_back({65, 65});
    seeds1.push_back({66, 66});
    seeds1.push_back({67, 67});
    score = count(seeds1);
    P_RR("Part1: %lld\n", score);
    //========================================================

    auto seeds2 = GetInitialSeeds2();
    score = count(seeds2);
    P_RR("Part2: %lld\n", score);
    return 0;
}
