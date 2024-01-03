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
            }
        }
    }
    return set.size();
}

VECI getPath(const std::vector<std::pair<LL,LL>>& map, const std::unordered_map<LL,VECI>& searchMap, LL from, LL to){
    std::queue<VECI> q;
    std::unordered_set<LL> set;
    set.reserve(2000);
    q.push(VECI{from});
    set.insert(from);
    VECI path;
    path.push_back(from);
    while(!q.empty()){
        VECI tmp_path = q.front();
        LL name = tmp_path.back();
        q.pop();
        for(const auto& m:searchMap.at(name)){
            if(set.count(m) == 0){
                VECI copy = tmp_path;
                copy.push_back(m);
                if(m == to){return copy;}
                q.push(copy);
                set.insert(m);
            }
        }
    }
    return path;
}

LL getBatch(const std::vector<std::pair<LL,LL>>& map, const std::unordered_map<LL,VECI>& searchMap, LL one, LL two){
    std::set<LL> set = {one, two};
    bool added = true;
    while(true) {
        added = false;
        for(auto base:set){
            const VECI& map = searchMap.at(base);
            for(auto cur:map){
                P(base, cur, set.count(cur), set.size());
                if(set.count(cur) == 0) {
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
    P(set);
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
    return getBatch(vec, searchMap, searchMap.begin()->first, std::next(searchMap.begin(),1)->first);
#if 0
    LL total = countConnected(vec, searchMap);
    result = total;
    std::thread ths[40];
    bool finished = false;
    FOR(i, vec.size()){
        if(ths[i%40].joinable()){
            ths[i%40].join();
        }
        ths[i%40] = std::thread([&result, vec, searchMap, total, i]{
            LL local = total;
            static std::mutex mut;
            for(LL j = i+1; j < vec.size(); ++j){
                for(LL k = j+1; k < vec.size(); ++k){
                    local = std::min( local, countConnected(vec, searchMap, i, j, k));
                    if(local < (total/2)) {
                        std::lock_guard<std::mutex> lock{mut};
                        result = local;
                        P(i,j,k, result, total);
                        return;
                    }
                }
                if(j%100 == 0){
                    std::lock_guard<std::mutex> lock{mut};
                    P(i, j, local, result, total);
                }
            }
            std::lock_guard<std::mutex> lock{mut};
            result = std::min(result, local);
            P(i, local, result, total);
        });
        // ths[i].join();
    }

    FOR(i, 40){
        if(ths[i].joinable()){
            ths[i].join();
        }
    }
    return result * (total - result);
#endif
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
