#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

std::map<S, std::tuple<S, S, LL>> M;

LL n = 0;

bool GetNext() {
    LL step = n%in[0].size();
    ++n;
    return in[0][step] == 'L';
}

auto count1() {
    LL result = 0;
    S cur = "AAA";
    while(cur != "ZZZ") {
        ++result;
        auto next = GetNext();
        auto nextS = next ? std::get<0>(M[cur]) : std::get<1>(M[cur]);
        if(cur == nextS) return 0LL;
        cur = nextS;
    }
    return result;
}

auto count2() {
    LL result = 0;
    std::vector<std::tuple<S, LL, LL>> results;
    for(auto& m : M) {
        if(m.first[2] == 'A') {
            for(auto& mm : M){
                std::get<2>(mm.second) = -1;
            }
            LL counter = 1;
            result = 0;
            n = 0;
            auto cur = m.first;
            // std::get<2>(m.second) = 0;
            auto* ptr = &M[cur];
            while(!((std::get<2>(*ptr) != -1) && (cur[2] == 'Z'))) {
                std::get<2>(*ptr) = result;
                ++result;
                auto next = GetNext();
                auto& second = M[cur];
                const auto& nextS = next ? std::get<0>(second) : std::get<1>(second);
                // P(cur, M[cur].first, M[cur].second, nextS, (next ? 'L' : 'R'));
                if(cur == nextS) return 0LL;
                cur = nextS;
                ptr = &M[cur];

                // if(result > 2) return 0LL;
                if(counter < result) {
                    P(counter, cur);
                    counter *= 10;
                }
            }
            results.push_back({m.first, std::get<2>(*ptr), result});
            P(m.first, std::get<2>(*ptr), result);
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    for(size_t i = 2; i < in.size();++i){
        auto v1 = splitStr(in[i], '=');
        auto v2 = splitStr(v1[1],',');
        S left(v2[0].begin()+1, v2[0].end());
        v2[1].pop_back();
        S right(v2[1].begin(), v2[1].end());
        M[v1[0]] = std::make_tuple(left, right, -1);
    }

    LL score = 0;
    n = 0;
    // score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
