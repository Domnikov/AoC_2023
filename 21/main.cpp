#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

class Elf {
  public:
    static inline LL counter = 0;
    LL id = counter++;
    LL row;
    LL col;
};

std::ostream& operator<<(std::ostream& os, const Elf& me) {
    os<<"Elf("<<me.id<<",["<<me.row<<","<<me.col<<"])";
    return os;
}

auto count1() {
    LL result = 0;

    return result;
}

auto count2() {
    LL result = 0;

    return result;
}

int main(int argc, char** argv)
{
    Elf e;
    P(e);
    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
