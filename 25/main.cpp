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
#if 0
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
#endif
LL getBatch(const std::vector<std::pair<S,S>>& map, const std::map<S,VECS>& searchMap, std::set<S> set){
    P(set);
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
                        // P(base, cur, count, s);
                    }
                }

                if(count >= 1) {
                    // P(base, cur, count, set.size());
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
            // LL i1 = s1[0] * 1000000+s1[1]*1000+s1[2];
            // LL i2 = s2[0] * 1000000+s2[1]*1000+s2[2];
            map.emplace(s1, s2);
            searchMap[s1].push_back(s2);
            searchMap[s2].push_back(s1);
        }
    }
    std::vector<std::pair<S,S>> vec(map.begin(), map.end());
    std::set<S> set;
    FillSet(set, searchMap, 2, 4);
    result = getBatch(vec, searchMap, set);
    P(result, searchMap.size()-result);
    return result * (searchMap.size()-result);
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
