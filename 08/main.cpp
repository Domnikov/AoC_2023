#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

std::map<S, std::pair<S,S>> M;

LL n = 0;

bool GetNext() {
    LL step = n%in.size();
    ++n;
    return in[0][step] == 'L';
}

auto count() {
    LL result = 0;
    S cur = "AAA";
    while(cur != "ZZZ") {
        ++result;
        auto next = GetNext();
        auto nextS = next ? M[cur].first : M[cur].second;
        P(cur, M[cur].first, M[cur].second, nextS, (next ? 'L' : 'R'));
        if(cur == nextS) return 0LL;
        cur = nextS;
    }
    return result;
}

int main(int argc, char** argv)
{
    for(size_t i = 2; i < in.size();++i){
        auto v1 = splitStr(in[i], '=');
        // P_VEC(v1);
        auto v2 = splitStr(v1[1],',');
        // P_VEC(v2);
        S left(v2[0].begin()+1, v2[0].end());
        v2[1].pop_back();
        S right(v2[1].begin(), v2[1].end());
        M[v1[0]] = std::make_pair(left, right);
    }

    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
