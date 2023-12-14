#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

bool is_emptyRow(LL l){
    FOR(i, in[l].size()){
        if(in[l][i] != '.') return false;
    }
    return true;
}

bool is_emptyCol(LL c){
    FOR(i, in.size()){
        if(in[i][c] != '.') return false;
    }
    return true;
}

void insertRow(LL l){
    in.insert(in.begin() + l+1, in[l]);
}

void insertCol(LL c){
    FOR(i, in.size()){
        in[c].insert(in[c].begin() + c+1, '.');
    }
}

void expand(){
    for(LL i = in.size() - 1; i >= 0; --i){
        if(is_emptyRow(i)){
            insertRow(i);
        }

    }
}

auto count() {
    LL result = 0;
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    P_VECV(in);
    expand();
    P_VECV(in);
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
