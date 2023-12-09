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
    return !is_numer(x,y) && c != '.';

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
    VECI adj;
    LL nan = -666;
    FOR(y, in.size()){
        LL num = nan;
        bool is_adj = false;
        FOR(x, in[y].size()){
            if(is_numer(x, y)){
                if(num == nan) num = 0;
                num = 10*num+(in[y][x]-0x30);
                is_adj |= is_adjacent(x,y);
            }
            else if(num != nan){
                if(is_adj){
                    adj.push_back(num);
                }
                num = nan;
                is_adj=false;
            }
        }
        if(num != nan){
            if(is_adj){
                adj.push_back(num);
            }
            num = nan;
            is_adj=true;
        }
    }
    for(auto n : adj){
        result += n;
    }
    return result;
}

auto get_num(LL x, LL y){
    std::pair<bool,std::pair<std::pair<LL,LL>,LL>> result {false, {{x, y}, 0}};
    if(is_numer(x, y)){
        LL begin = x;
        while(is_numer(x, y)){
            --x;
        }
        ++x;
        LL num = 0;
        while(is_numer(x, y)) {
            num = num * 10 + (in[y][x]-0x30);
            ++x;
        }
        --x;
        result.first = true;
        result.second.first = std::make_pair(x, y);
        result.second.second = num;
    }
    return result;
}

auto get_nums(LL x, LL y) {
    std::map<std::pair<LL, LL>, LL> nums;

    auto num = get_num(x-1, y-1); if(num.first){ nums[num.second.first] = num.second.second; P(x-1, y-1, num.second.second);}
         num = get_num(x-1, y  ); if(num.first){ nums[num.second.first] = num.second.second; P(x-1, y  , num.second.second);}
         num = get_num(x-1, y+1); if(num.first){ nums[num.second.first] = num.second.second; P(x-1, y+1, num.second.second);}
         num = get_num(x  , y-1); if(num.first){ nums[num.second.first] = num.second.second; P(x  , y-1, num.second.second);}
         num = get_num(x  , y+1); if(num.first){ nums[num.second.first] = num.second.second; P(x  , y+1, num.second.second);}
         num = get_num(x+1, y-1); if(num.first){ nums[num.second.first] = num.second.second; P(x+1, y-1, num.second.second);}
         num = get_num(x+1, y  ); if(num.first){ nums[num.second.first] = num.second.second; P(x+1, y  , num.second.second);}
         num = get_num(x+1, y+1); if(num.first){ nums[num.second.first] = num.second.second; P(x+1, y+1, num.second.second);}

    VECI result;
    TRANSFORM(nums, result, [](auto n){return n.second;});
    P_VEC(result);
    return result;
}

auto get_gears(){
    std::map<std::pair<LL, LL>, VECI> gears;
    FOR(y, in.size()){
        FOR(x, in[y].size()){
            if(in[y][x] == '*'){
                auto nums = get_nums(x, y);
                gears[std::make_pair(x, y)] = nums;
            }
        }
    }
    return gears;
}

LL count_gears() {
    LL result = 0;
    auto gears = get_gears();
    for(auto g : gears){

        if(g.second.size() == 2){
            result += g.second[0]*g.second[1];
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count_gears();
    P_RR("Part2: %lld\n", score);
    return 0;
}
