#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL Y(LL n){
    return n/in[0].size();
}

LL X(LL n){
    return n%in[0].size();
}

char Get(LL n){
    return in[Y(n)][X(n)];
}

LL findStart(){
    FOR(i, in.size()*in[0].size()){
        if(Get(i) == 'S'){
            return i;
        }
    }
    exit(1);
}

auto count() {
    LL result = 0;
    result = findStart();
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
