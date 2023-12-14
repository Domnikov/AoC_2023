#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

void MoveNorth(LL row, LL col){
    // P_RR("void MoveNorth(%lld, %lld)", row, col);
    for(LL r = row-1; r >= 0; --r){
        if(in[r][col] == '.') {
            // P_RR(".");
            in[r][col] = 'O';
            in[r+1][col] = '.';
        } else {
            // P_RR("\n");
            return;
        }
    }
    // P_RR("\n");
}

LL GetPerRow(LL row) {
    LL sum = 0;
    FOR(col, in[row].size()){
        if(in[row][col] == 'O') {
            ++sum;
        }
    }
    return sum;
}

LL GetScore(){
    LL score = 0;
    FOR(row, in.size()){
        LL dist = in.size() - row;
        LL rocks = GetPerRow(row);
        P(rocks, dist);
        score += rocks*dist;
    }
    return score;
}

auto count1() {
    LL result = 0;
    // P_VECV(in);
    FOR(row, in.size()){
        if(row == 0) continue;
        FOR(col, in[row].size()){
            if(in[row][col] == 'O'){
                MoveNorth(row,col);
            }
        }
    }
    // P_RR("\n");
    // P_VECV(in);
    result = GetScore();
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
