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
using Path = std::tuple<LL, LL, Dir, VECI>;
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

auto ExtractMinPos(std::vector<Path>& vec) {
    if(vec.empty()) {
        P_LINE;
        exit(1);
    }
    auto it = std::min_element(BE(vec), [](auto a, auto b){return std::get<1>(a) < std::get<1>(b);});
    auto result = *it;
    vec.erase(it);
    return result;
}

bool exist(LL pos, VECI path) {
    return std::any_of(BE(path), [pos](const auto& p){return pos == p;});
}

Dir IsThreeSame(const std::vector<Path>& vec) {
    if(vec.size() < 3) {
        return Dir::None;
    }
    LL x1 = GetX(std::get<0>(vec.back()));
    LL x2 = GetX(std::get<0>(vec[vec.size() - 3]));
    LL y1 = GetY(std::get<0>(vec.back()));
    LL y2 = GetY(std::get<0>(vec[vec.size() - 3]));

    if((x1-x2) ==-3) return Dir::Left ;
    if((x1-x2) == 3) return Dir::Right;
    if((y1-y2) ==-3) return Dir::Up   ;
    if((y1-y2) == 3) return Dir::Down ;

    return Dir::None;
}

void AddNewPos(LL pos, LL score, Dir d, VECI path, std::vector<Path>& vec) {
    try{if(/*d != Dir::Left  &&*/IsThreeSame(vec) != Dir::Left ) { LL newPos = pos; LL newScore = score; VECI newPath = path;FOR(i, 1) { newPos = ToLeft (pos); if(exist(newPos, path)){break;} newPath.push_back(newPos);newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Left , newPath); } }}catch(S s){}
    try{if(/*d != Dir::Right &&*/IsThreeSame(vec) != Dir::Right) { LL newPos = pos; LL newScore = score; VECI newPath = path;FOR(i, 1) { newPos = ToRight(pos); if(exist(newPos, path)){break;} newPath.push_back(newPos);newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Right, newPath); } }}catch(S s){}
    try{if(/*d != Dir::Up    &&*/IsThreeSame(vec) != Dir::Up   ) { LL newPos = pos; LL newScore = score; VECI newPath = path;FOR(i, 1) { newPos = ToUp   (pos); if(exist(newPos, path)){break;} newPath.push_back(newPos);newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Up   , newPath); } }}catch(S s){}
    try{if(/*d != Dir::Down  &&*/IsThreeSame(vec) != Dir::Down ) { LL newPos = pos; LL newScore = score; VECI newPath = path;FOR(i, 1) { newPos = ToDown (pos); if(exist(newPos, path)){break;} newPath.push_back(newPos);newScore += GetScore(newPos); vec.emplace_back(newPos, newScore, Dir::Down , newPath); } }}catch(S s){}
}

auto count1() {
    LL result = 0;
    LL endPos = GetPos(X-1, Y-1);

    std::vector<Path> points;
    points.emplace_back(0, GetScore(0), Dir::Up, VECI{0});
    // SetC(0, '*');
    // P_VECV(in);
    // P_RR("\n");

    for(LL i = 0;!points.empty() && i < 10;++i){
        auto [pos, score, d, path] = ExtractMinPos(points);
        if(pos == endPos) {
            return score;
        }
        SetC(pos, '*');
        AddNewPos(pos, score, d, path, points);
        // P(pos, score, points);
        P_VECV(in);
        P_RR("\n");
    }

    P(points);

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
