#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();
std::map<std::pair<LL,LL>, LL> tiles1;

enum class Dir {
    Left = 0x1,
    Right = 0x10,
    Up = 0x100,
    Down = 0x1000,
};

bool isLeft (LL d) { return d & (LL)Dir::Left ; }
bool isRight(LL d) { return d & (LL)Dir::Right; }
bool isUp   (LL d) { return d & (LL)Dir::Up   ; }
bool isDown (LL d) { return d & (LL)Dir::Down ; }

void Beam(LL row, LL col, Dir d) {
    do {

    } while ();
}

LL count1() {
    Beam(0,0,Dir::Right);

    return tiles1.size();
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
