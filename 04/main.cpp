#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

VECI getHaveWins(VECI wins, VECI my) {
    VECI have;
    std::set<LL> win_list;
    std::copy(BE(wins), std::inserter(win_list, win_list.begin()));
    for(auto n : my) {
        if(win_list.count(n))
        {
            have.push_back(n);
        }
    }
    return have;
}

LL getScore(LL N)
{
    if(N == 0){return 0;}
    LL score = 1;
    FOR(n, N-1){
        score *= 2;
    }
    return score;
}

auto count() {
    LL result = 0;
    for(auto s : in){
        auto card = stoi(splitStr(splitStr(s,':')[0], ' ')[1]);
        auto swins = splitStr(splitStr(splitStr(s, ':')[1], '|')[0], ' ');
        auto smy = splitStr(splitStr(splitStr(s, ':')[1], '|')[1], ' ');
        VECI wins, my;
        VECSTOA(swins, wins);
        VECSTOA(smy, my);
        result += getScore(getHaveWins(wins, my).size());
    }
    return result;
}

VECI win_cards;

auto count_2() {
    LL result = 0;
    for(auto s : in){
        auto card = stoi(splitStr(splitStr(s,':')[0], ' ')[1]);
        auto swins = splitStr(splitStr(splitStr(s, ':')[1], '|')[0], ' ');
        auto smy = splitStr(splitStr(splitStr(s, ':')[1], '|')[1], ' ');
        VECI wins, my;
        VECSTOA(swins, wins);
        VECSTOA(smy, my);
        auto win_orig = getHaveWins(wins, my).size();
        auto cards = win_cards[card-1] + 0;
        for(LL i = 0; i < win_orig && (i+card) < in.size(); ++i) {
            win_cards[card+i] += cards;
        }
    }
    for(auto c: win_cards){
        result += c;
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================
    win_cards = VECI(in.size(), 1);
    score = count_2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
