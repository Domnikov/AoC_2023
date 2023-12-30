#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL countConnected(const std::vector<std::pair<S,S>>& map){
    std::queue<S> q;
    std::set<S> set;
    q.push(map.begin()->first);
    set.insert(q.front());
    while(!q.empty()){
        S name = q.front();
        q.pop();
        for(const auto& s:map){
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
                auto modified = vec;
                modified.erase(modified.begin() + k);
                modified.erase(modified.begin() + j);
                modified.erase(modified.begin() + i);
                result = std::min(result, countConnected(modified));
            }
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
