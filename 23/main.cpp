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
    }
    Path(std::pair<LL,LL> pos, const Path& old){
        cur = pos;
        score=old.score+1;
        path = old.path;
        path.emplace_back(cur);
    }
    std::pair<LL,LL> cur;
    LL score;
    VECPLL path;
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

auto count2() {
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
        P(cur, p.path);
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

int main(int argc, char** argv)
{
    LL score = 0;
    // score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
