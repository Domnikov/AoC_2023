#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <cassert>
#include <queue>
#include <list>

auto in = getInput();
auto in2 = getInput();

constexpr bool USE_PATH = true;

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
using Path = std::tuple<LL, LL, Dir, LL, VECI>;
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

LL ToLeft (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x <= 0) { return -1; } return GetPos(x-1, y  ); }
LL ToRight(LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x>=X-1) { return -1; } return GetPos(x+1, y  ); }
LL ToUp   (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y <= 0) { return -1; } return GetPos(x  , y-1); }
LL ToDown (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y>=Y-1) { return -1; } return GetPos(x  , y+1); }

char GetC(LL pos){
    return in[GetY(pos)][GetX(pos)];
}

void SetC(LL pos, char c, VECS& table = in){
    auto x = GetX(pos);
    auto y = GetY(pos);
    if(x < 0 || y < 0 || x >= X || y >= Y) {
        P_LINE;
        P(x, y, pos, c);
        exit(1);
    }
    table[y][x] = c;
}

LL GetScore(LL pos){
    auto c = GetC(pos);
    if (c >= 0x30 && c <= 0x39) {
        if(c == 0x30){
            P(pos);
        }
        return GetC(pos) - 0x30;
    }
    return -1;
}

std::list<Path> points;
std::map<LL, LL> passed;

Path GetMin(){
    auto it = std::min_element(BE(points), [](const auto& a, const auto& b){return (std::get<1>(a) < std::get<1>(b));});
    assert(it != points.end());
    auto path = *it;
    points.erase(it);
    passed.emplace(std::get<0>(path), std::get<1>(path));
    return path;
}

void InsertIfLess(LL newPos, LL newScore, Dir dir, LL dir_count, const VECI& path) {
    if(passed.count(newPos)){
        if(passed[newPos] < newScore) {
            return;
        } else {
            passed.erase(newPos);
        }
    }
    auto it = std::find_if(BE(points), [newPos](const auto& a){return std::get<0>(a) == newPos;});
    if(it == points.end()){
        points.emplace_back(newPos, newScore, dir, dir_count, path);
        SetC(newPos, '*', in2);
    } else if(newScore < std::get<1>(*it)) {
        *it = Path{newPos, newScore, dir, dir_count, path};
    }
}

void InsertIfCorrect(LL newPos, LL newScore, Dir dir, LL dir_count, const VECI& path) {
    if(path.size() >= 3) {
        LL x5 = GetX(path[path.size()-5]);
        LL x4 = GetX(path[path.size()-4]);
        LL x3 = GetX(path[path.size()-3]);
        LL x2 = GetX(path[path.size()-2]);
        LL x1 = GetX(path[path.size()-1]);

        LL y5 = GetY(path[path.size()-5]);
        LL y4 = GetY(path[path.size()-4]);
        LL y3 = GetY(path[path.size()-3]);
        LL y2 = GetY(path[path.size()-2]);
        LL y1 = GetY(path[path.size()-1]);

        if((x1 == x2 && x2 == x3 && x3 == x4 && x4 == x5) || (y1 == y2 && y2 == y3 && y3 == y4 && y4 == y5)) {
            return;
        }
    }

    points.emplace_back(newPos, newScore, dir, dir_count, path);
}

void AddNew(LL pos, LL score, Dir dir, LL dir_count, const VECI& path) {
    if(dir != Dir::Right){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+1); newPath = path;} LL newDirCount =  0; for(LL i = 0;i< 1;++i){newPos = ToLeft (newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfCorrect(newPos, newScore, Dir::Left , newDirCount+i+1, newPath);}}
    if(dir != Dir::Left ){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+1); newPath = path;} LL newDirCount =  0; for(LL i = 0;i< 1;++i){newPos = ToRight(newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfCorrect(newPos, newScore, Dir::Right, newDirCount+i+1, newPath);}}
    if(dir != Dir::Down ){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+1); newPath = path;} LL newDirCount =  0; for(LL i = 0;i< 1;++i){newPos = ToUp   (newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfCorrect(newPos, newScore, Dir::Up   , newDirCount+i+1, newPath);}}
    if(dir != Dir::Up   ){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+1); newPath = path;} LL newDirCount =  0; for(LL i = 0;i< 1;++i){newPos = ToDown (newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfCorrect(newPos, newScore, Dir::Down , newDirCount+i+1, newPath);}}
}

void AddNew3(LL pos, LL score, Dir dir, LL dir_count, const VECI& path) {
    if(dir != Dir::Right){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+3); newPath = path;} LL newDirCount =  (dir != Dir::Left ) ? 0 : dir_count; for(LL i = 0;i< 3-newDirCount;++i){newPos = ToLeft (newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfLess(newPos, newScore, Dir::Left , newDirCount+i+1, newPath);}}
    if(dir != Dir::Left ){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+3); newPath = path;} LL newDirCount =  (dir != Dir::Right) ? 0 : dir_count; for(LL i = 0;i< 3-newDirCount;++i){newPos = ToRight(newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfLess(newPos, newScore, Dir::Right, newDirCount+i+1, newPath);}}
    if(dir != Dir::Down ){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+3); newPath = path;} LL newDirCount =  (dir != Dir::Up   ) ? 0 : dir_count; for(LL i = 0;i< 3-newDirCount;++i){newPos = ToUp   (newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfLess(newPos, newScore, Dir::Up   , newDirCount+i+1, newPath);}}
    if(dir != Dir::Up   ){LL newPos = pos; LL newScore = score; VECI newPath; if(USE_PATH){newPath.reserve(path.size()+3); newPath = path;} LL newDirCount =  (dir != Dir::Down ) ? 0 : dir_count; for(LL i = 0;i< 3-newDirCount;++i){newPos = ToDown (newPos); if(newPos == -1){break;} LL sc = GetScore(newPos); if(sc == -1){break;} newScore += sc; if(USE_PATH){newPath.push_back(newPos);}InsertIfLess(newPos, newScore, Dir::Down , newDirCount+i+1, newPath);}}
}

auto count1() {
    LL result = 0;
    LL endPos = GetPos(X-1, Y-1);

    points.emplace_back(0, GetScore(0), Dir::Up, 0, VECI{0});
    LL counter = 100;
    for(LL i = 0;!points.empty() && i < 100;++i){
        auto [pos, score, dir, dir_count, path] = GetMin();
        SetC(pos, '#', in2);
        if(pos == endPos) {
            auto newIn = getInput();
            for(auto p:path){
                SetC(p,'*', newIn);
            }
            P_VECV(newIn);
            P_VECV(in);
            return score;
        }
        AddNew(pos, score, dir, dir_count, path);
        // P(i, pos, score, dir, dir_count, path)
        // for(const auto& p:points) {
        //     P(p);
        // }
    }

    P("Not found!!!");
    // for(auto pnt:points){
    //     LL p = std::get<0>(pnt);
    //     SetC(p,'*', newIn);
    // }
    P_VECV(in2);
    for(const auto& p:points) {
        P(p);
    }

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
