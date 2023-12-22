#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <cassert>
#include <queue>
#include <list>

auto in = getInput();
LL N = 1000;

VECS field;

struct PP{
    LL row;
    LL col;
};

std::ostream& operator<<(std::ostream& s, PP p){
    s<<'['<<p.col<<','<<p.col<<']';
    return s;
}

void Go(char c, LL num, PP& point){
    switch(c){
        case 'R':
            point.row+=num;
            break;
        case 'L':
            point.row-=num;
            break;
        case 'U':
            point.col+=num;
            break;
        case 'D':
            point.col-=num;
            break;
    }
    assert(point.row < 0 || point.col < 0 || point.row >= N || point.col >= N);
}

auto count1() {
    LL result = 0;
    field.clear();
    FOR(n, N) {
        field.push_back(S(N, '.'));
    }
    PP ss{300,300};

    for(const auto& s: in){
        auto vec = splitStr(s, ' ');
        char dir = vec[0][0];
        LL num = stoi(vec[1]);
        S color = vec[2];

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
