#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL countConnected(const std::vector<std::pair<LL,LL>>& map, LL i = -1, LL j = -1, LL k = -1){
    std::queue<LL> q;
    std::set<LL> set;
    for(LL idx = 0;q.empty();++idx){
        if(idx == i || idx == j || idx == k){
            continue;
        }
        q.push(map[idx].first);
    }
    set.insert(q.front());
    while(!q.empty()){
        LL name = q.front();
        q.pop();
        for(LL idx = 0;idx < map.size();++idx){
            if(idx == i || idx == j || idx == k){
                continue;
            }
            auto& s = map[idx];
            LL other = -1;
            if(s.first == name){
                other = s.second;
            }
            if(s.second == name){
                other = s.first;
            }
            if(other == -1){
                continue;
            }
            if(set.count(other) == 0){
                q.push(other);
                set.insert(other);
            }
        }
    }
    return set.size();
}

auto count1() {
    LL result = 0;

    std::set<std::pair<LL, LL>> map;

    for(const auto& s:in) {
        auto vec = splitStr(s, ':');
        auto vec1 = splitStr(vec[1], ' ');
        for(const auto& v:vec1){
            S s1 = vec[0] < v ? vec[0] : v;
            S s2 = s1 == v ? vec[0] : v;
            LL i1 = s1[0] * 1000000+s1[1]*1000+s1[2];
            LL i2 = s2[0] * 1000000+s2[1]*1000+s2[2];
            map.emplace(i1, i2);
        }
    }
    std::vector<std::pair<LL,LL>> vec(map.begin(), map.end());
    LL total = countConnected(vec);
    result = total;
    FOR(i, vec.size()){
        for(LL j = i+1; j < vec.size(); ++j){
            for(LL k = j+1; k < vec.size(); ++k){
                result = std::min(result, countConnected(vec, i, j, k));
                P(k);
            }
            P(j);
        }
        P(i);
    }

    return result * (total - result);
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
