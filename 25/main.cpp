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

LL countConnected(const std::vector<std::pair<LL,LL>>& map, const std::unordered_map<LL,VECI>& searchMap, LL i = -1, LL j = -1, LL k = -1){
    std::queue<LL> q;
    std::unordered_set<LL> set;
    set.reserve(2000);
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
        for(const auto& m:searchMap.at(name)){
            if(i >= 0 && name == map[i].first && m == map[i].second){
                continue;
            }
            if(j >= 0 && name == map[j].first && m == map[j].second){
                continue;
            }
            if(k >= 0 && name == map[k].first && m == map[k].second){
                continue;
            }
            if(set.count(m) == 0){
                q.push(m);
                set.insert(m);
                if(i != -1 && set.size() > 750) return 2000;
            }
        }
        // for(LL idx = 0;idx < map.size();++idx){
        //     if(idx == i || idx == j || idx == k){
        //         continue;
        //     }
        //     auto& s = map[idx];
        //     LL other = -1;
        //     if(s.first == name){
        //         other = s.second;
        //     }
        //     if(s.second == name){
        //         other = s.first;
        //     }
        //     if(other == -1){
        //         continue;
        //     }
        //     if(set.count(other) == 0){
        //         q.push(other);
        //         set.insert(other);
        //     }
        // }
    }
    return set.size();
}

auto count1() {
    LL result = 0;

    std::set<std::pair<LL, LL>> map;
    std::unordered_map<LL,VECI>searchMap;

    for(const auto& s:in) {
        auto vec = splitStr(s, ':');
        auto vec1 = splitStr(vec[1], ' ');
        for(const auto& v:vec1){
            S s1 = vec[0] < v ? vec[0] : v;
            S s2 = s1 == v ? vec[0] : v;
            LL i1 = s1[0] * 1000000+s1[1]*1000+s1[2];
            LL i2 = s2[0] * 1000000+s2[1]*1000+s2[2];
            map.emplace(i1, i2);
            searchMap[i1].push_back(i2);
            searchMap[i2].push_back(i1);
        }
    }
    std::vector<std::pair<LL,LL>> vec(map.begin(), map.end());
    LL total = countConnected(vec, searchMap);
    result = total;
    std::thread ths[40];
    bool finished = false;
    FOR(i, vec.size()){
        if(ths[i%40].joinable()){
            ths[i%40].join();
        }
        ths[i%40] = std::thread([&result, vec, searchMap, total, i]{
            static std::mutex mut;
            for(LL j = i+1; j < vec.size(); ++j){
                for(LL k = j+1; k < vec.size(); ++k){
                    LL local = countConnected(vec, searchMap, i, j, k);
                    if(local < (total/2)) {
                        std::lock_guard<std::mutex> lock{mut};
                        result = local;
                        P(i,j,k, result, total);
                        return;
                    }
                }
                std::lock_guard<std::mutex> lock{mut};
            }
            P(i, result, total);
        });
        // ths[i].join();
    }

    FOR(i, 40){
        if(ths[i].joinable()){
            ths[i].join();
        }
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
