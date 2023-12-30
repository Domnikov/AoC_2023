#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL countConnected(const std::vector<std::pair<S,S>>& map, LL i = -1, LL j = -1, LL k = -1){
    std::queue<S> q;
    std::set<S> set;
    for(LL idx = 0;q.empty();++idx){
        if(idx == i || idx == j || idx == k){
            continue;
        }
        q.push(map[idx].first);
    }
    set.insert(q.front());
    while(!q.empty()){
        S name = q.front();
        q.pop();
        for(LL idx = 0;idx < map.size();++idx){
            if(idx == i || idx == j || idx == k){
                continue;
            }
            auto& s = map[idx];
            S other;
            if(s.first == name){
                other = s.second;
            }
            if(s.second == name){
                other = s.first;
            }
            if(other.empty()){
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

    std::set<std::pair<S, S>> map;

    for(const auto& s:in) {
        auto vec = splitStr(s, ':');
        auto vec1 = splitStr(vec[1], ' ');
        for(const auto& v:vec1){
            S s1 = vec[0] < v ? vec[0] : v;
            S s2 = s1 == v ? vec[0] : v;
            map.emplace(s1, s2);
        }
    }
    std::vector<std::pair<S,S>> vec(map.begin(), map.end());
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
