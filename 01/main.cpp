#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

auto transform(S str) {
    ReplaceAll(str, "one", "1");
    ReplaceAll(str, "two", "2");
    ReplaceAll(str, "three", "3");
    ReplaceAll(str, "four", "4");
    ReplaceAll(str, "five", "5");
    ReplaceAll(str, "six", "6");
    ReplaceAll(str, "seven", "7");
    ReplaceAll(str, "eight", "8");
    ReplaceAll(str, "nine", "9");
    return str;
}

auto count(bool use_words) {
    LL result = 0;
    for(auto aa: in) {
        S a = use_words ? transform(aa) : aa;
        for(auto c:a){
            if (c >= 0x30 && c <= 0x39){
                result += 10*(c - 0x30);
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
    score = count(false);
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count(true);
    P_RR("Part2: %lld\n", score);
    return 0;
}
