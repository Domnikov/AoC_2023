#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <functional>
#include <queue>
#include <list>

auto in = getInput();

VECI getPairs1(VECI sc) {
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


struct Hand1 {
    Hand1(S s) {
        auto vec = splitStr(s, ' ');
        cards = vec[0];
        bid = stoll(vec[1]);
        sc = VECI(5,0);
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
        pairs = getPairs1(sc);
        // P(cards);
        // P_VEC(sc);
        // P_VEC(pairs);
    }

    S cards;
    LL bid;
    VECI sc;
    VECI pairs;
};

std::ostream& operator<<( std::ostream& dest, const Hand1& h)
{
    dest << "("<< h.cards << " "<<h.bid<<")";
    return dest;
}


bool IsFive     (const Hand1& h){return h.pairs[0] == 5;}
bool IsFour     (const Hand1& h){return h.pairs[0] == 4;}
bool IsFull     (const Hand1& h){return h.pairs[0] == 3 && h.pairs[1] == 2;}
bool IsThree    (const Hand1& h){return h.pairs[0] == 3 && h.pairs[1] == 1;}
bool IsTwoPair  (const Hand1& h){return h.pairs[0] == 2 && h.pairs[1] == 2;}
bool IsOnePair  (const Hand1& h){return h.pairs[0] == 2 && h.pairs[1] == 1;}
bool IsNoPair   (const Hand1& h){return h.pairs[0] == 1;}

bool bareComp(const Hand1& lhs, const Hand1& rhs) {
    FOR(i, lhs.sc.size()){
        if(lhs.sc[i] < rhs.sc[i]){
            return true;
        }
        if(lhs.sc[i] > rhs.sc[i]){
            return false;
        }
    }
    exit(1);
}

bool operator < (const Hand1& lhs, const Hand1& rhs) {
    std::vector<std::function<bool(const Hand1&)>> cmpFunc{{
        [](const Hand1& h){return IsFive   (h);},
        [](const Hand1& h){return IsFour   (h);},
        [](const Hand1& h){return IsFull   (h);},
        [](const Hand1& h){return IsThree  (h);},
        [](const Hand1& h){return IsTwoPair(h);},
        [](const Hand1& h){return IsOnePair(h);},
        [](const Hand1& h){return IsNoPair (h);},
    }};

    for(const auto& func : cmpFunc) {
        if(func(lhs) || func(rhs)) {
            return func(lhs) == func(rhs) ? bareComp(lhs, rhs) : func(rhs);
        }
    }
    exit(1);
}

auto count1() {
    LL result = 0;
    std::vector<Hand1> hands;
    for(const auto& s:in) {
        hands.push_back(Hand1{s});
    }
    // P_VEC(hands);
    std::sort(BE(hands));
    // P_VEC(hands);
    FOR(i, hands.size()){
        LL idx = i+1;
        LL score = idx*hands[i].bid;
        // P(idx, hands[i].bid, score);
        result += score;
    }
    return result;
}

VECI getPairs2(VECI sc) {
    VECI result;
    std::sort(BE(sc));
    while(!sc.empty() && sc.back() != 1) {
        LL cur = sc.back();
        sc.pop_back();
        result.push_back(1);
        while(cur == sc.back()){
            sc.pop_back();
            result.back()++;
        }
    }
    std::sort(BE(result), [](LL a, LL b){return a>b;});
    if(result.empty()) result.push_back(0);
    result[0] += sc.size();
    return result;
}


struct Hand2 {
    Hand2(S s) {
        auto vec = splitStr(s, ' ');
        cards = vec[0];
        bid = stoll(vec[1]);
        sc = VECI(5,0);
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
                case 'T':
                    sc[i] = 10;
                    break;
                case '9':
                    sc[i] = 9;
                    break;
                case '8':
                    sc[i] = 8;
                    break;
                case '7':
                    sc[i] = 7;
                    break;
                case '6':
                    sc[i] = 6;
                    break;
                case '5':
                    sc[i] = 5;
                    break;
                case '4':
                    sc[i] = 4;
                    break;
                case '3':
                    sc[i] = 3;
                    break;
                case '2':
                    sc[i] = 2;
                    break;
                case 'J':
                    sc[i] = 1;
                    break;
            }
        }
        pairs = getPairs2(sc);
        // P(cards);
        // P_VEC(sc);
        // P_VEC(pairs);
    }

    S cards;
    LL bid;
    VECI sc;
    VECI pairs;
};

std::ostream& operator<<( std::ostream& dest, const Hand2& h)
{
    dest << "("<< h.cards << " "<<h.bid<<")";
    return dest;
}


bool IsFive     (const Hand2& h){return h.pairs[0] == 5;}
bool IsFour     (const Hand2& h){return h.pairs[0] == 4;}
bool IsFull     (const Hand2& h){return h.pairs[0] == 3 && h.pairs[1] == 2;}
bool IsThree    (const Hand2& h){return h.pairs[0] == 3 && h.pairs[1] == 1;}
bool IsTwoPair  (const Hand2& h){return h.pairs[0] == 2 && h.pairs[1] == 2;}
bool IsOnePair  (const Hand2& h){return h.pairs[0] == 2 && h.pairs[1] == 1;}
bool IsNoPair   (const Hand2& h){return h.pairs[0] == 1;}

bool bareComp(const Hand2& lhs, const Hand2& rhs) {
    FOR(i, lhs.sc.size()){
        if(lhs.sc[i] < rhs.sc[i]){
            return true;
        }
        if(lhs.sc[i] > rhs.sc[i]){
            return false;
        }
    }
    exit(1);
}

bool operator < (const Hand2& lhs, const Hand2& rhs) {
    std::vector<std::function<bool(const Hand2&)>> cmpFunc{{
        [](const Hand2& h){return IsFive   (h);},
        [](const Hand2& h){return IsFour   (h);},
        [](const Hand2& h){return IsFull   (h);},
        [](const Hand2& h){return IsThree  (h);},
        [](const Hand2& h){return IsTwoPair(h);},
        [](const Hand2& h){return IsOnePair(h);},
        [](const Hand2& h){return IsNoPair (h);},
    }};

    for(const auto& func : cmpFunc) {
        if(func(lhs) || func(rhs)) {
            return func(lhs) == func(rhs) ? bareComp(lhs, rhs) : func(rhs);
        }
    }
    exit(1);
}


auto count2() {
    LL result = 0;
    std::vector<Hand2> hands;
    for(const auto& s:in) {
        hands.push_back(Hand2{s});
    }
    P_LINE;
    // P_VEC(hands);
    std::sort(BE(hands));
    // P_VEC(hands);
    FOR(i, hands.size()){
        LL idx = i+1;
        LL score = idx*hands[i].bid;
        // P(idx, hands[i].bid, score);
        result += score;
    }
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
