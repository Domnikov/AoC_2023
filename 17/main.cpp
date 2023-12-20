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
LL MAX_SCORE = (in.size() + in[0].size()) * 6;

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

LL ToLeft (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x == 0) { return -1; } return GetPos(x-1, y  ); }
LL ToRight(LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x>=X-1) { return -1; } return GetPos(x+1, y  ); }
LL ToUp   (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y == 0) { return -1; } return GetPos(x  , y-1); }
LL ToDown (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y>=Y-1) { return -1; } return GetPos(x  , y+1); }

char GetC(LL pos){
    return in[GetY(pos)][GetX(pos)];
}

void SetC(LL pos, char c, VECS& table = in){
    table[GetY(pos)][GetX(pos)] = c;
}

char GetScore(LL pos){
    auto c = GetC(pos);
    if (c >= 0x30 && c <= 0x39)
        return GetC(pos) - 0x30;
    return -1;
}

auto ExtractMinPos(std::list<Path>& vec) {
    if(vec.empty()) {
        P_LINE;
        exit(1);
    }
    auto it = std::min_element(BE(vec), [](auto a, auto b){return std::get<1>(a) < std::get<1>(b);});
    auto result = *it;
    vec.erase(it);
    return result;
}

bool exist(LL pos, const VECI& path) {
    return std::any_of(BE(path), [pos](const auto& p){return pos == p;});
}

Dir IsThreeSame(const VECI& vec) {
    if(vec.size() < 3) {
        return Dir::None;
    }
    LL p1 = vec[vec.size() - 1];
    LL p4 = vec[vec.size() - 4];

    if((GetX(p4) - GetX(p1)) == 3) { return Dir::Left ; }
    if((GetX(p1) - GetX(p4)) == 3) { return Dir::Right; }
    if((GetY(p4) - GetY(p1)) == 3) { return Dir::Up   ; }
    if((GetY(p1) - GetY(p4)) == 3) { return Dir::Down ; }

    return Dir::None;
}

void AddNewPos(LL pos, LL score, Dir d, const VECI& path, std::list<Path>& vec) {
    if(/*d != Dir::Left  &&*/IsThreeSame(path) != Dir::Left ) { LL newPos = pos; LL newScore = score; FOR(i, 1) { newPos = ToLeft (pos); if(newPos == -1) {break;}newScore += GetScore(newPos);if(newScore == -1){break;}/*if(exist(newPos, path)){break;}*/VECI newPath; newPath.reserve(path.size()+1); newPath = path; newPath.push_back(newPos); if(newScore > MAX_SCORE) {break;} vec.emplace_back(newPos, newScore, Dir::Left , std::move(newPath)); } }
    if(/*d != Dir::Right &&*/IsThreeSame(path) != Dir::Right) { LL newPos = pos; LL newScore = score; FOR(i, 1) { newPos = ToRight(pos); if(newPos == -1) {break;}newScore += GetScore(newPos);if(newScore == -1){break;}/*if(exist(newPos, path)){break;}*/VECI newPath; newPath.reserve(path.size()+1); newPath = path; newPath.push_back(newPos); if(newScore > MAX_SCORE) {break;} vec.emplace_back(newPos, newScore, Dir::Right, std::move(newPath)); } }
    if(/*d != Dir::Up    &&*/IsThreeSame(path) != Dir::Up   ) { LL newPos = pos; LL newScore = score; FOR(i, 1) { newPos = ToUp   (pos); if(newPos == -1) {break;}newScore += GetScore(newPos);if(newScore == -1){break;}/*if(exist(newPos, path)){break;}*/VECI newPath; newPath.reserve(path.size()+1); newPath = path; newPath.push_back(newPos); if(newScore > MAX_SCORE) {break;} vec.emplace_back(newPos, newScore, Dir::Up   , std::move(newPath)); } }
    if(/*d != Dir::Down  &&*/IsThreeSame(path) != Dir::Down ) { LL newPos = pos; LL newScore = score; FOR(i, 1) { newPos = ToDown (pos); if(newPos == -1) {break;}newScore += GetScore(newPos);if(newScore == -1){break;}/*if(exist(newPos, path)){break;}*/VECI newPath; newPath.reserve(path.size()+1); newPath = path; newPath.push_back(newPos); if(newScore > MAX_SCORE) {break;} vec.emplace_back(newPos, newScore, Dir::Down , std::move(newPath)); } }
}

auto count1() {
    LL result = 0;
    LL endPos = GetPos(X-1, Y-1);

    std::list<Path> points;
    points.emplace_back(0, /*GetScore(0)*/0, Dir::Up, VECI{0});
    // SetC(0, '*');
    // P_VECV(in);
    // P_RR("\n");
    LL counter = 1;
    for(LL i = 0;!points.empty() && i < 10000000;++i){
        auto [pos, score, d, path] = ExtractMinPos(points);
        if(pos == endPos) {
            in = getInput();
            LL sc = 0;
            for(auto p: path){
                sc += GetScore(p);
                SetC(p, '*');
            }
            P(sc);
            P_VECV(in);
            P_RR("\n");
            // Dir d1 = std::get<2>(path[path.size() - 1]);
            // Dir d2 = std::get<2>(path[path.size() - 2]);
            // Dir d3 = std::get<2>(path[path.size() - 3]);
            //
            // P(d1, d2, d3);
            return score;
        }
        SetC(pos, '*');
        AddNewPos(pos, score, d, path, points);
        if( (i % 10000) == 0 ) {
            P(counter, score, points.size());
            auto input_copy = getInput();
            for(auto p: path){
                SetC(p, '*', input_copy);
            }
            P_VECV(input_copy);
        }
        // P(pos, score, points);
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
