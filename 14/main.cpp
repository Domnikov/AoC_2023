#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

void MoveNorth(LL row, LL col){
    for(LL r = row-1; r >= 0; --r){
        if(in[r][col] == '.') {
            in[r][col] = 'O';
            in[r+1][col] = '.';
        } else {
            return;
        }
    }
}

void MoveSouth(LL row, LL col){
    for(LL r = row+1; r < in.size(); ++r){
        if(in[r][col] == '.') {
            in[r][col] = 'O';
            in[r-1][col] = '.';
        } else {
            return;
        }
    }
}

void MoveWest(LL row, LL col){
    for(LL c = col-1; c >= 0; --c){
        if(in[row][c] == '.') {
            in[row][c] = 'O';
            in[row][c+1] = '.';
        } else {
            return;
        }
    }
}

void MoveEast(LL row, LL col){
    for(LL c = col+1; c < in[0].size(); ++c){
        if(in[row][c] == '.') {
            in[row][c] = 'O';
            in[row][c-1] = '.';
        } else {
            return;
        }
    }
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
        score += rocks*dist;
    }
    return score;
}

auto count1() {
    LL result = 0;
    FOR(row, in.size()){
        if(row == 0) continue;
        FOR(col, in[row].size()){
            if(in[row][col] == 'O'){
                MoveNorth(row,col);
            }
        }
    }
    result = GetScore();
    return result;
}

void oneRoll(){
    FOR(row, in.size()){
        if(row == 0) continue;
        FOR(col, in[row].size()){
            if(in[row][col] == 'O'){
                MoveNorth(row,col);
            }
        }
    }
    FOR(row, in.size()){
        FOR(col, in[row].size()){
            if(col == 0) continue;
            if(in[row][col] == 'O'){
                MoveWest(row,col);
            }
        }
    }
    FOR(i, in.size()){
        if(i == 0) continue;
        auto row = in.size() - 1 - i;
        FOR(col, in[row].size()){
            if(in[row][col] == 'O'){
                MoveSouth(row,col);
            }
        }
    }
    FOR(row, in.size()){
        FOR(i, in[row].size()){
            if(i == 0) continue;
            auto col = in[row].size() - 1 - i;
            if(in[row][col] == 'O'){
                MoveEast(row,col);
            }
        }
    }
}

auto count2() {
    LL result = 0;
    // P_RR(".....\n");
    // P_VECV(in);
    FOR(row, in.size()){
        FOR(col, in[row].size()){
            if(col == 0) continue;
            if(in[row][col] == 'O'){
                MoveWest(row,col);
            }
        }
    }
    // P_RR(".....\n");
    // P_VECV(in);
    FOR(i, in.size()){
        if(i == 0) continue;
        auto row = in.size() - 1 - i;
        FOR(col, in[row].size()){
            if(in[row][col] == 'O'){
                MoveSouth(row,col);
            }
        }
    }
    // P_RR(".....\n");
    // P_VECV(in);
    FOR(row, in.size()){
        FOR(i, in[row].size()){
            if(i == 0) continue;
            auto col = in[row].size() - 1 - i;
            if(in[row][col] == 'O'){
                MoveEast(row,col);
            }
        }
    }
    // P_RR(".....\n");
    // P_VECV(in);
    LL N = 999999999;
    std::map<VECS, LL> results;
    results[in] = 0;
    bool begin = true;
    FOR(i, N) {
        oneRoll();
        if(results.count(in)){
            auto period = i+1 - results[in];
            auto to_add = (N - i*10)/period;
            i += to_add*period;
            begin = false;
        }
        if(begin)results[in] = i + 1;
        P(i, results.size(),results.count(in));
    }

    // for(const auto& m:results){
        // P_RR("%lld\t", m.first);
        // P_VEC(m.second);
    //     P(m.second.size());
    // }

    result = GetScore();
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
