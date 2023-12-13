#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <functional>
#include <queue>
#include <list>

auto in = getInput();

VECI getPairs(VECI sc) {
    VECI result;
    std::sort(BE(sc));
    while(!sc.empty()) {
        LL cur = sc.back();
        sc.pop_back();
        result.push_back(1);
        while(cur == sc.back()){
            sc.pop_back();
            result.back()++;
        }
    }
    std::sort(BE(result), [](LL a, LL b){return a>b;});
    return result;
}


struct Hand {
    Hand(S s) {
        return;
        auto vec = splitStr(s, ' ');
        cards = vec[0];
        bid = stoll(vec[1]);
        sc = VECI(0,5);
        for(size_t i = 0; i < 5;++i){
            char c = cards[i];
            switch(c) {
                case 'A':
                    sc[i] = 13;
                    break;
                case 'K':
                    sc[i] = 12;
                    break;
                case 'Q':
                    sc[i] = 11;
                    break;
                case 'J':
                    sc[i] = 10;
                    break;
                case 'T':
                    sc[i] = 9;
                    break;
                case '9':
                    sc[i] = 8;
                    break;
                case '8':
                    sc[i] = 7;
                    break;
                case '7':
                    sc[i] = 6;
                    break;
                case '6':
                    sc[i] = 5;
                    break;
                case '5':
                    sc[i] = 4;
                    break;
                case '4':
                    sc[i] = 3;
                    break;
                case '3':
                    sc[i] = 2;
                    break;
                case '2':
                    sc[i] = 1;
                    break;
            }
        }
        pairs = getPairs(sc);
    }

    S cards;
    LL bid;
    VECI sc;
    VECI pairs;
};

bool IsFive     (const Hand& h){return h.pairs[0] == 5;}
bool IsFour     (const Hand& h){return h.pairs[0] == 4;}
bool IsFull     (const Hand& h){return h.pairs[0] == 3 && h.pairs[1] == 2;}
bool IsThree    (const Hand& h){return h.pairs[0] == 3 && h.pairs[1] == 1;}
bool IsTwoPair  (const Hand& h){return h.pairs[0] == 2 && h.pairs[1] == 2;}
bool IsOnePair  (const Hand& h){return h.pairs[0] == 2 && h.pairs[1] == 1;}
bool IsNoPair   (const Hand& h){return h.pairs[0] == 1;}

bool bareComp(const Hand& lhs, const Hand& rhs) {
    return false;
}

bool operator < (const Hand& lhs, const Hand& rhs) {
    std::vector<std::function<bool(const Hand&)>> cmpFunc{{
        [](const Hand& h){return IsFive   (h);},
        [](const Hand& h){return IsFour   (h);},
        [](const Hand& h){return IsFull   (h);},
        [](const Hand& h){return IsThree  (h);},
        [](const Hand& h){return IsTwoPair(h);},
        [](const Hand& h){return IsOnePair(h);},
        [](const Hand& h){return IsNoPair (h);},
    }};

    for(const auto& func : cmpFunc) {
        if(func(lhs) || func(rhs)) {
            return func(lhs) == func(rhs) ? bareComp(lhs, rhs) : func(rhs);
        }
    }
    exit(1);
}

std::ostream& operator<<( std::ostream& dest, Hand h)
{
    dest << "("<< h.cards << " "<<h.bid<<")";
    return dest;
}

auto count() {
    LL result = 0;
    std::vector<Hand> hands;
    for(const auto& s:in) {
        hands.push_back(Hand{s});
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
