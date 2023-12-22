#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

VECS field;

struct PP{
    LL row;
    LL col;
};

std::ostream& operator<<(std::ostream& s, PP p){
    s<<'['<<p.col<<','<<p.col<<']';
    return s;
}

auto count1() {
    LL result = 0;
    field.clear();
    LL N = 1000;
    FOR(n, N) {
        field.push_back(S(N, '.'));
    }
    PP ss{300,300};

    for(const auto& s: in){
        char dir = splitStr(s, ' ')[0][0];
        LL num = stoi(splitStr(s, ' ')[1]);
        S color = splitStr(s, 'n')[2];

        P(dir, nut, color);
    }


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
