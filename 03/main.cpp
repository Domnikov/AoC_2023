#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>
#include <set>

auto in = getInput();

char get(LL x, LL y) {
    return in[y][x];
}

bool is_numer(LL x, LL y){
    if(x < 0 || y < 0 || y >= in.size() || x >= in[y].size()) {
        return false;
    }
    auto c = get(x,y);
    return c >= 0x30 && c <= 0x39;

}

bool if_simbol(LL x, LL y){
    if(x < 0 || y < 0 || y >= in.size() || x >= in[y].size()) {
        return false;
    }
    auto c = get(x,y);
    return !is_numer(x,y) || c == '.';

}

bool is_adjacent(LL x, LL y) {
    return if_simbol(x - 1, y - 1) ||
           if_simbol(x - 0, y - 1) ||
           if_simbol(x + 1, y - 1) ||
           if_simbol(x - 1, y - 0) ||
           if_simbol(x + 1, y - 0) ||
           if_simbol(x - 1, y + 1) ||
           if_simbol(x - 0, y + 1) ||
           if_simbol(x + 1, y + 1);
}

auto count() {
    LL result = 0;
    VECI not_adj;
    LL nan = -666;
    FOR(y, in.size()){
        LL num = nan;
        bool is_adj = true;
        FOR(x, in[y].size()){
            if(is_numer(x, y)){
                num = 10*num+(in[y][x]-0x30);
            }
            else if(num != nan){
                if(is_adj){
                    not_adj.push_back(num);
                }
                num = nan;
                is_adj=true;
            }
        }
    }
    P_VEC(not_adj);
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
