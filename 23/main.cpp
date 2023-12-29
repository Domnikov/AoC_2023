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
    q.emplace(0,1);
    while(!q.empty()){
        auto p = q.front();
        if(p.cur.first == in.size()-1){
            result = std::max(result, p.score);
            continue;
        }
        q.pop();
        auto cur = p.cur;
        P(cur);
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
            q.emplace(newPos, p);
        }
    }

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
