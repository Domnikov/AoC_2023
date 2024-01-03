#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <mutex>
#include <thread>
#include <queue>
#include <list>

auto in = getInput();

LL getBatch(const std::vector<std::pair<S,S>>& map, const std::map<S,VECS>& searchMap, std::set<S> set){

    bool added = true;
    while(added) {
        added = false;
        for(auto base:set){
            const VECS& map = searchMap.at(base);
            for(auto cur:map){
                if(set.count(cur)) continue;
                LL count = 0;
                const VECS& adjmap = searchMap.at(cur);
                for(auto s:adjmap){
                    if(s!=base && set.count(s)){
                        ++count;
                    }
                }

                if(count >= 1) {
                    set.insert(cur);
                    added = true;
                    break;
                }
            }
            if(added == true){
                break;
            }
        }
    }
    return set.size();
}

void FillSet(std::set<S>& set, const std::map<S, VECS>& map, LL shift, LL depth){
    set.insert(std::next(map.begin(), shift)->first);
    FOR(i, depth) {
        std::queue<S> q;
        std::for_each(BE(set), [&q](auto s){q.push(s);});
        while(!q.empty()){
            S key = q.front();
            q.pop();
            set.insert(key);
            for(auto s:map.at(key)){
                set.insert(s);
            }
        }
    }
}

auto count1() {
    LL result = 0;

    std::set<std::pair<S, S>> map;
    std::map<S,VECS>searchMap;

    for(const auto& s:in) {
        auto vec = splitStr(s, ':');
        auto vec1 = splitStr(vec[1], ' ');
        for(const auto& v:vec1){
            S s1 = vec[0] < v ? vec[0] : v;
            S s2 = s1 == v ? vec[0] : v;
            map.emplace(s1, s2);
            searchMap[s1].push_back(s2);
            searchMap[s2].push_back(s1);
        }
    }
    std::vector<std::pair<S,S>> vec(map.begin(), map.end());
    std::set<S> set;
    FillSet(set, searchMap, 2, 4);
    result = getBatch(vec, searchMap, set);
    return result * (searchMap.size()-result);
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count1();
    P_RR("Part Final: %lld\n", score);

    return 0;
}
