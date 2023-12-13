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

LL find_LCM(VECI vec){
    auto is_all_div = [&vec](LL n){
        for(auto v : vec){
            if((n % v) != 0) {
                return false;
            }
        }
        return true;
    };
    LL n = vec[0];
    while(!is_all_div(n)) {
        n += vec[0];
    }
    return n;
}

LL count2() {
    VECI vec;
    LL result = 0;
    for(auto& m : M) {
        if(m.first[2] == 'A') {
            std::map<std::pair<S, LL>, LL> finds;
            S cur = m.first;
            result = 0;
            n = 0;
            LL N = in[0].size();
            while(cur[2] != 'Z' || finds[std::make_pair(cur, n%N)] == 5) {
                if(cur[2] == 'Z') {
                    P(cur[2], n%N, finds.count({cur, n%N}), result);
                    finds[std::make_pair(cur, n%N)] = finds[std::make_pair(cur, n%N)] + 1;
                }
                ++result;
                auto next = GetNext();
                auto nextS = next ? std::get<0>(M[cur]) : std::get<1>(M[cur]);
                // if(cur == nextS) return 0LL;
                cur = nextS;
                // P(cur[2], finds.count({cur, n%N}));
            }
            vec.push_back(result);
        }
    }
    P_VEC(vec);
    return find_LCM(vec);
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
