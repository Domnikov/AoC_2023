#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

void MoveNorth(LL row, LL col){
    P_RR("void MoveNorth(%lld, %lld)", row, col);
    for(LL r = row-1; r >= 0; --r){
        if(in[row][col] == '.') {
            in[row][col] = 'O';
            in[row+1][col] = '.';
        } else {
            return;
        }
    }
}

auto count1() {
    LL result = 0;
    P_VECV(in);
    FOR(row, in.size()){
        if(row == 0) continue;
        FOR(col, in[row].size()){
            if(in[row][col] == 'O'){
                MoveNorth(row,col);
            }
        }
    }
    P_RR("\n");
    P_VECV(in);
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
