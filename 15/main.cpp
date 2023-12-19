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
        if(c == ',') {
            result += hash;
            hash = 0;
        } else {
            hash += c;
            hash *= 17;
            hash %= 256;
        }
    }

    result += hash;
    return result;
}

enum class SIGN {NO_SET,MINUS, EQ};

auto count2() {
    LL result = 0;
    LL hash = 0;
    S s;
    SIGN sign = SIGN::NO_SET;
    LL num = 0;
    S lbl;
    std::map<LL, std::vector<std::pair<S,LL>>> boxes;
    for(auto c:in[0]){
        if(c == '=') {
            sign  = SIGN::EQ;
        } else if (c == '-') {
            sign = SIGN::MINUS;
        }

        if(c >= '0' && c <= '9')
        {
            num = num*10 + c - 0x30;
        }

        if(sign == SIGN::NO_SET){
            lbl += c;
            hash += c;
            hash *= 17;
            hash %= 256;
        }

        if(c == ',') {
            // auto& box = boxes[hash];
            //
            // auto it = std::find(BE(box), [lbl](const auto& pair){ return lbl == pair.first;});
            //
            // if(sign == SIGN::MINUS){
            //     box.erase(it);
            // } else if(sign == SIGN::EQ) {
            //     if(it == box.end()) {
            //         box.emplace_back(lbl, num);
            //     } else {
            //         it->second = num;
            //     }
            // } else {P_LINE; exit(1);}
            //
            // // P(s, hash, lbl, num, (int)sign);
            P_MAP(boxes);

            num = 0;
            sign = SIGN::NO_SET;
            lbl.clear();
            s.clear();
            hash = 0;
        } else {
            s += c;
        }
    }

    result += hash;
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
