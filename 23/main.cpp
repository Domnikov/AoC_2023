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
        row=r;
        col=c;
        score = 1;
        path.emplace_back(r,c);
    }
    Path(LL r, LL c, const Path& old){
        row=r;
        col=c;
        score=old.score+1;
        path = old.path;
        path.emplace_back(r,c);
    }
    LL row;
    LL col;
    LL score;
    VECPLL path;
};

auto count1() {
    LL result = 0;
    std::queue<Path> q;
    q.emplace(0,1);
    while(!q.empty()){
        auto p = q.front();
        q.pop();
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
