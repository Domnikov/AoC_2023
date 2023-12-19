#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

auto count1() {
    LL result = 0;
    LL hash = 0;
    for(auto c:in[0]){
        P(c);
        if(c == ',') {
            result += hash;
            hash = 0;
        } else {
            P(hash);
            hash += c;
            P(hash);
            hash *= 17;
            P(hash);
            hash %= 256;
            P(hash);
        }
    }

    result += hash;
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
