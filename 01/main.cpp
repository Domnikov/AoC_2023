#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();
using slpair = std::pair<S, LL>;
std::vector<slpair> pattern1 = {{"1", 1},
                                {"2", 2},
                                {"3", 3},
                                {"4", 4},
                                {"5", 5},
                                {"6", 6},
                                {"7", 7},
                                {"8", 8},
                                {"9", 9}};

std::vector<slpair> pattern2 = {{"1", 1},
                                {"2", 2},
                                {"3", 3},
                                {"4", 4},
                                {"5", 5},
                                {"6", 6},
                                {"7", 7},
                                {"8", 8},
                                {"9", 9},
                                {"one", 1},
                                {"two", 2},
                                {"three", 3},
                                {"four", 4},
                                {"five", 5},
                                {"six", 6},
                                {"seven", 7},
                                {"eight", 8},
                                {"nine", 9}};

LL getFirst(S str, std::vector<slpair> pattern) {
    LL sel;
    size_t min = str.size();
    for(auto p : pattern){
        auto pos = str.find(p.first, 0);
        if(pos == std::string::npos) continue;
        if(pos < min) {
            min = pos;
            sel = p.second;
        }
    }
    return sel;
}

LL getLast(S str, std::vector<slpair> pattern) {
    LL sel;
    size_t min = str.size();
    for(auto p : pattern){
        auto pos = str.rfind(p.first, 0);
        if(pos == std::string::npos) continue;
        if(pos < min) {
            min = pos;
            sel = p.second;
        }
    }
    return sel;
}

auto count(std::vector<slpair> pattern) {
    LL result = 0;
    for(auto s:in){
        result+= getFirst(s, pattern)*10+getLast(s, pattern);
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count(pattern1);
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count(pattern2);
    P_RR("Part2: %lld\n", score);
    return 0;
}
