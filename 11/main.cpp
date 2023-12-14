#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

void expand(){
    for(size_t i = in.size() - 1; i >= 0; --i){

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
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
