#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

auto count() {
    LL result = 0;
    for(auto a: in) {
        for(auto c:a){
            if (c >= 0x30 && c <= 0x39){
                result *= 10*(c - 0x30);
                break;
            }
        }
        FOR(i, a.size()) {
            LL c = a[a.size()- 1 - i];
            if (c >= 0x30 && c <= 0x39){
                result += c - 0x30;
                break;
            }
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
    score = 0;

    P_RR("Part2: %lld\n", score);
    return 0;
}
