#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL X = in[0].size();
LL Y = in.size();

enum class Dir {
    None  = 0,
    Left  = 0x1,
    Right = 0x10,
    Up    = 0x100,
    Down  = 0x1000,
};

namespace std{

    inline ostream& operator<<( ostream& dest, Dir d )
    {
        switch (d) {
            case Dir::None : dest << "None "; break;
            case Dir::Left : dest << "Left "; break;
            case Dir::Right: dest << "Right"; break;
            case Dir::Up   : dest << "Up   "; break;
            case Dir::Down : dest << "Down "; break;
        }
        return dest;
    }
}

LL GetX(LL pos) {
    return pos % X;
}

LL GetY(LL pos) {
    return pos / X;
}

LL GetPos(LL x, LL y) {
    return y*X + x;
}

LL ToLeft (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x == 0) { throw S("x < 0"); } return GetPos(x-1, y  ); }
LL ToRight(LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x>=X-1) { throw S("x > X"); } return GetPos(x+1, y  ); }
LL ToUp   (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y == 0) { throw S("y < 0"); } return GetPos(x  , y-1); }
LL ToDown (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y>=Y-1) { throw S("y > Y"); } return GetPos(x  , y+1); }

char GetC(LL pos){
    return in[GetY(pos)][GetX(pos)];
}

void SetC(LL pos, char c){
    in[GetY(pos)][GetX(pos)] = c;
}

char GetScore(LL pos){
    auto c = GetC(pos);
    if (c >= 0x30 && c <= 0x39)
        return GetC(pos) - 0x30;
    throw S("Not a score: ") + c;
}

auto ExtractMinPos(std::vector<std::tuple<LL, LL, Dir>>& vec) {
    if(vec.empty()) {
        P_LINE;
        exit(1);
    }
    auto it = std::min_element(BE(vec), [](auto a, auto b){return std::get<1>(a) < std::get<1>(b);});
    auto result = *it;
    vec.erase(it);
    return result;
}

void AddNewPos(LL pos, LL score, Dir d, std::vector<std::tuple<LL, LL, Dir>>& vec) {
    try{if(d != Dir::Left ) { LL newPos = pos; LL newScore = score; FOR(i, 3) { newPos = ToLeft (pos); newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Left ); } }}catch(S s){}
    try{if(d != Dir::Right) { LL newPos = pos; LL newScore = score; FOR(i, 3) { newPos = ToRight(pos); newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Right); } }}catch(S s){}
    try{if(d != Dir::Up   ) { LL newPos = pos; LL newScore = score; FOR(i, 3) { newPos = ToUp   (pos); newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Up   ); } }}catch(S s){}
    try{if(d != Dir::Down ) { LL newPos = pos; LL newScore = score; FOR(i, 3) { newPos = ToDown (pos); newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Down ); } }}catch(S s){}
}

auto count1() {
    LL result = 0;
    LL endPos = GetPos(X-1, Y-1);

    std::vector<std::tuple<LL, LL, Dir>> points;
    points.emplace_back(0, GetScore(0), Dir::Up);
    SetC(0, '*');
    P_VECV(in);
    P_RR("\n");

    while(!points.empty()){
        auto [pos, score, d] = ExtractMinPos(points);
        if(pos == endPos) {
            return score;
        }
        AddNewPos(pos, score, d, points);
        P(pos, score, points);
        P_VECV(in);
        P_RR("\n");
    }

    P("Not found!!!");

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
