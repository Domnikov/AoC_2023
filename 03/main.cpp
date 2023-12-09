#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>
#include <set>

auto in = getInput();

std::map<std::pair<LL,LL>,VECI> gears;

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
    return !is_numer(x,y) && c != '.';

}

bool if_star(LL x, LL y){
    if(x < 0 || y < 0 || y >= in.size() || x >= in[y].size()) {
        return false;
    }
    auto c = get(x,y);
    return c == '*';

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

bool isGear(LL x, LL y) {
    return if_star(x - 1, y - 1) ||
           if_star(x - 0, y - 1) ||
           if_star(x + 1, y - 1) ||
           if_star(x - 1, y - 0) ||
           if_star(x + 1, y - 0) ||
           if_star(x - 1, y + 1) ||
           if_star(x - 0, y + 1) ||
           if_star(x + 1, y + 1);
}

auto count() {
    LL result = 0;
    VECI adj;
    LL nan = -666;
    FOR(y, in.size()){
        LL num = nan;
        bool is_adj = false;
        bool is_gear = false;
        FOR(x, in[y].size()){
            if(is_numer(x, y)){
                if(num == nan) num = 0;
                num = 10*num+(in[y][x]-0x30);
                is_adj |= is_adjacent(x,y);
                is_gear |= isGear(x,y);
            }
            else if(num != nan){
                if(is_adj){
                    adj.push_back(num);
                }
                num = nan;
                is_adj=false;
                is_gear = false;
            }
        }
        if(num != nan){
            if(is_adj){
                adj.push_back(num);
            }
            num = nan;
            is_adj=true;
            is_gear = false;
        }
    }
    for(auto n : adj){
        result += n;
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = 0;

    for(auto gear : gears)
    {
        auto v = gear.second;
        if(v.size() == 2){
            score += v[0]*v[1];
        }
    }

    P_RR("Part2: %lld\n", score);
    return 0;
}
