#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

struct Path{
    Path(LL r, LL c) {
        cur = {r, c};
        score = 1;
        path.emplace_back(cur);
        set.insert(cur);
    }
    Path(std::pair<LL,LL> pos, const Path& old){
        cur = pos;
        score=old.score+1;
        path = old.path;
        path.emplace_back(cur);
        set.insert(cur);
    }
    std::pair<LL,LL> cur;
    LL score;
    VECPLL path;
    std::set<std::pair<LL,LL>> set;
};

VECPLL Mods{{-1,0},{1,0},{0,-1},{0,1}};
S Slopes = "^v<>";

auto count1() {
    LL result = 0;
    std::queue<Path> q;
    Path init(0,1);
    q.emplace(std::pair<LL,LL>{1,1}, init);
    for(LL i = 0;i < 10000000000 && !q.empty();++i){
        auto p = q.front();
        q.pop();
        if(p.cur.first == in.size()-1){
            result = std::max(result, p.score);
            continue;
        }
        auto cur = p.cur;
        // P(cur, p.path);
        FOR(i, Mods.size()) {
            if(in[cur.first][cur.second] != '.') {
                if(in[cur.first][cur.second] != Slopes[i]){
                    continue;
                }
            }
            const auto& m = Mods[i];
            auto newPos = cur+m;
            if(in[newPos.first][newPos.second] == '#') {
                continue;
            }
            if(p.path[p.path.size()-2] == newPos) {
                continue;
            }
            q.emplace(newPos, p);
        }
    }
    while(!q.empty()){
        auto qq = q.front();
        q.pop();
        // P(qq.cur, qq.score, qq.path);
    }

    return result-1;
}

bool TillNextCrossRoad(Path& path) {
    bool running = true;
    std::pair<LL,LL> endcr1{113, 125};
    std::pair<LL,LL> endcr2{137, 111};
    P_LINE;
    while(running) {
    P_LINE;
        auto cur = path.cur;
        auto prev = path.path[path.path.size()-2];
        std::pair<LL,LL> valid_next;
        LL ways_count = 0;
    P_LINE;
        FOR(i, Mods.size()) {
    P_LINE;
            const auto& m = Mods[i];
            auto newPos = cur+m;
    P_LINE;
            if(prev == newPos) {
                continue;
            }
    P_LINE;
    P(newPos);
            if(newPos.first < 0) return false;
            if(in[newPos.first][newPos.second] == '#') {
                continue;
            }
    P_LINE;
    P_LINE;
            // if(/*(path.set.count(endcr1) && path.set.count(endcr1)) ||*/ path.set.count(newPos)){
            // // if(std::find_if(BE(path.path), [newPos, ends = 0](const auto& p)mutable{
            // //                 if(p == std::make_pair(113LL, 125LL) || p == std::make_pair(137LL, 111LL)) {
            // //                     ends++;
            // //                 }
            // //                 return ends == 2 || p == newPos;
            // //             }) != path.path.end()) {
            //     continue;
            // }
    P_LINE;
            ways_count++;
    P_LINE;
            valid_next = newPos;
    P_LINE;
            if(newPos.first == in.size()-1) {
                running = false;
                break;
            }
    P_LINE;
        }
    P_LINE;
        if(ways_count == 1){
            path.path.push_back(valid_next);
            path.cur = valid_next;
            path.score++;
        } else if(ways_count == 0) {
            return false;
        } else {
            running = false;
        }
    }
    return path.set.count(path.cur);
    // (113, 125)
    //     (137,111)
}

auto count2() {
    LL result = 0;
    std::queue<Path> q;
    Path init(0,1);
    q.emplace(std::pair<LL,LL>{1,1}, init);
    LL point = 1;
    for(LL i = 0;!q.empty();++i){
        auto p = q.front();
        q.pop();
        if(p.cur.first == in.size()-1){
            result = std::max(result, p.score);
            continue;
        }
        auto cur = p.cur;
        // P(cur, p.path);
        FOR(i, Mods.size()) {
            const auto& m = Mods[i];
            auto newPos = cur+m;
            // P(newPos, p.path);
            if(in[newPos.first][newPos.second] == '#') {
                continue;
            }
            // q.emplace(newPos, p);
            Path newPath{newPos, p};
            if(TillNextCrossRoad(newPath)){
                newPath.set.insert(newPath.cur);
                q.push(newPath);
            }
        }
        if(i > point){
            P(point, q.size(), result);
            point *= 10;
        }
    }
    while(!q.empty()){
        auto qq = q.front();
        q.pop();
        // P(qq.cur, qq.score, qq.path);
    }

    return result-1;
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
