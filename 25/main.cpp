#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL countConnected(const std::map<S,VECS>& map){
    std::queue<S> q;
    std::set<S> set;
    q.push(map.begin()->first);
    set.insert(map.begin()->first);
    while(!q.empty()){
        S name = q.front();
        q.pop();
        for(const auto& s:map.at(name)){
            if(set.count(s) == 0){
                q.push(s);
                set.insert(s);
            }
        }
    }
    return set.size();
}

auto count1() {
    LL result = 0;

    std::map<S, VECS> map;

    for(const auto& s:in) {
        auto vec = splitStr(s, ':');
        auto vec1 = splitStr(vec[1], ' ');
        map[vec[0]].insert(map[vec[0]].end(), BE(vec1));
        for(const auto& v:vec1){
            map[v].push_back(vec[0]);
        }
    }
    P_MAPV(map);

    P(map.size(), countConnected(map));

    return result;
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
