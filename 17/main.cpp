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

std::pair<LL,LL> JumpLeft (LL pos, LL n, VECI& path) {
    LL score = 0;
    FOR(i,n){
        pos = ToLeft(pos);
        if(pos == -1){
            return {-1,-1};
        }
        if(std::find(path.begin(), path.end(), pos) != path.end()) {
            return {-1,-1};
        }
        path.push_back(pos);
        LL newScore = GetScore(pos);
        if(newScore == -1){
            return {-1,-1};
        }
        score += newScore;
    }
    return {pos, score};
}

std::pair<LL,LL> JumpRight (LL pos, LL n, VECI& path) {
    LL score = 0;
    FOR(i,n){
        pos = ToRight(pos);
        if(pos == -1){
            return {-1,-1};
        }
        if(std::find(path.begin(), path.end(), pos) != path.end()) {
            return {-1,-1};
        }
        path.push_back(pos);
        LL newScore = GetScore(pos);
        if(newScore == -1){
            return {-1,-1};
        }
        score += newScore;
    }
    return {pos, score};
}

std::pair<LL,LL> JumpUp (LL pos, LL n, VECI& path) {
    LL score = 0;
    FOR(i,n){
        pos = ToUp(pos);
        if(pos == -1){
            return {-1,-1};
        }
        if(std::find(path.begin(), path.end(), pos) != path.end()) {
            return {-1,-1};
        }
        path.push_back(pos);
        LL newScore = GetScore(pos);
        if(newScore == -1){
            return {-1,-1};
        }
        score += newScore;
    }
    return {pos, score};
}

std::pair<LL,LL> JumpDown (LL pos, LL n, VECI& path) {
    LL score = 0;
    FOR(i,n){
        pos = ToDown(pos);
        if(pos == -1){
            return {-1,-1};
        }
        if(std::find(path.begin(), path.end(), pos) != path.end()) {
            return {-1,-1};
        }
        path.push_back(pos);
        LL newScore = GetScore(pos);
        if(newScore == -1){
            return {-1,-1};
        }
        score += newScore;
    }
    return {pos, score};
}

struct Q {
    Q(LL p, LL s, Dir d, LL dc, VECI path = {})
        :pos(p),score(s),dir(d),dir_count(dc), path(path)
    {}
    LL pos;
    LL score;
    Dir dir;
    LL dir_count;
    VECI path;
};

inline std::ostream& operator<<( std::ostream& dest, Q q )
{
    dest<<"[pos="<<q.pos<<",score="<<q.score<<","<<q.dir<<",dc="<<q.dir_count<<",path:"<<q.path<<']';
    return dest;
}

using Point = std::map<Dir, VECI>;
std::vector<Point> matrix;
std::vector<Q> queue;

Q GetMin(){
    auto it = std::min_element(BE(queue), [](const auto& a, const auto& b){return a.score < b.score;});
    assert(it != queue.end());
    auto path = *it;
    queue.erase(it);
    return path;
}

bool CheckAndInsert(LL& newPos, LL& score, Dir& dir, LL& dir_count, VECI& path, Dir newDir, LL n) {
    // if(dir == newDir && dir_count >= n) return false;
    if(newPos == -1) return false;
    LL newScore = GetScore(newPos);
    if(newScore == -1) return false;
    // score += newScore;

    if(std::find(path.begin(), path.end(), newPos) != path.end()) {
        return false;
    }

    dir_count = (dir == newDir) ? dir_count+1 : 0;
    dir = newDir;
    if(USE_PATH) {path.push_back(newPos);}
    auto& oldScore = matrix[newPos][dir][dir_count];
    if(newPos == GetPos(X-1, Y-1)) {
        auto newIn = getInput();
        for(auto p:path){
            SetC(p,'*', newIn);
        }
        P_VECV(newIn);
        P(score);
    }
    if(oldScore > score) {
        oldScore = score;
        queue.emplace_back(newPos, score, dir, dir_count, path);
        SetC(newPos, '*', in2);
    }
    return true;
}

void AddLeft (LL pos, LL score, Dir dir, LL dir_count, const VECI& path, LL jumpN, LL n){
    VECI newPath;
    if(USE_PATH) {newPath.reserve(path.size()+10); newPath = path;}
    auto [newPos, newScore] = JumpLeft(pos, jumpN, newPath);
    if(newPos == -1) return;
    pos = newPos;
    score += newScore;
    FOR(i,n) {
        pos = ToLeft(pos);
        if(pos == -1) return;
        newScore = GetScore(pos);
        if(newScore == -1) return;
        score += newScore;
        if(!CheckAndInsert(pos, score, dir, dir_count, newPath, Dir::Left, n)) return;
    }
}

void AddRight(LL pos, LL score, Dir dir, LL dir_count, const VECI& path, LL jumpN, LL n){
    VECI newPath;
    if(USE_PATH) {newPath.reserve(path.size()+10); newPath = path;}
    auto [newPos, newScore] = JumpRight(pos, jumpN, newPath);
    if(newPos == -1) return;
    pos = newPos;
    score += newScore;
    FOR(i,n){
        pos = ToRight(pos);
        if(pos == -1) return;
        newScore = GetScore(pos);
        if(newScore == -1) return;
        score += newScore;
        if(!CheckAndInsert(pos, score, dir, dir_count, newPath, Dir::Right, n)) return;
    }
}

void AddUp   (LL pos, LL score, Dir dir, LL dir_count, const VECI& path, LL jumpN, LL n){
    VECI newPath;
    if(USE_PATH) {newPath.reserve(path.size()+10); newPath = path;}
    auto [newPos, newScore] = JumpUp(pos, jumpN, newPath);
    if(newPos == -1) return;
    pos = newPos;
    score += newScore;
    FOR(i,n){
        pos = ToUp(pos);
        if(pos == -1) return;
        newScore = GetScore(pos);
        if(newScore == -1) return;
        score += newScore;
        if(!CheckAndInsert(pos, score, dir, dir_count, newPath, Dir::Up, n)) return;
    }
}

void AddDown (LL pos, LL score, Dir dir, LL dir_count, const VECI& path, LL jumpN, LL n){
    VECI newPath;
    if(USE_PATH) {newPath.reserve(path.size()+10); newPath = path;}
    auto [newPos, newScore] = JumpDown(pos, jumpN, newPath);
    if(newPos == -1) return;
    pos = newPos;
    score += newScore;
    FOR(i,n){
        pos = ToDown(pos);
        if(pos == -1) return;
        newScore = GetScore(pos);
        if(newScore == -1) return;
        score += newScore;
        if(!CheckAndInsert(pos, score, dir, dir_count, newPath, Dir::Down, n)) return;
    }
}

void AddNew(LL pos, LL score, Dir dir, LL dir_count, const VECI& path) {
    if(dir == Dir::Up    || dir == Dir::Down                    ){AddLeft (pos,score,dir,dir_count, path, 1, 3);}
    if(dir == Dir::Up    || dir == Dir::Down || dir == Dir::None){AddRight(pos,score,dir,dir_count, path, 1, 3);}
    if(dir == Dir::Left  || dir == Dir::Right                   ){AddUp   (pos,score,dir,dir_count, path, 1, 3);}
    if(dir == Dir::Left  || dir == Dir::Right|| dir == Dir::None){AddDown (pos,score,dir,dir_count, path, 1, 3);}
}

void AddNew2(LL pos, LL score, Dir dir, LL dir_count, const VECI& path) {
    if(dir == Dir::Up    || dir == Dir::Down                    ){AddLeft (pos,score,dir,dir_count, path, 3, 7);}
    if(dir == Dir::Up    || dir == Dir::Down || dir == Dir::None){AddRight(pos,score,dir,dir_count, path, 3, 7);}
    if(dir == Dir::Left  || dir == Dir::Right                   ){AddUp   (pos,score,dir,dir_count, path, 3, 7);}
    if(dir == Dir::Left  || dir == Dir::Right|| dir == Dir::None){AddDown (pos,score,dir,dir_count, path, 3, 7);}
}

auto count1() {
    LL endPos = GetPos(X-1, Y-1);

    FOR(i, X*Y){
        Point map;
        map[Dir::Left ] = VECI{999999999,999999999,999999999};
        map[Dir::Right] = VECI{999999999,999999999,999999999};
        map[Dir::Up   ] = VECI{999999999,999999999,999999999};
        map[Dir::Down ] = VECI{999999999,999999999,999999999};
        matrix.push_back(map);
    }

    queue.emplace_back(0, 0, Dir::None, 0, VECI{0});

    for(LL i = 0;!queue.empty();++i){
        auto [pos, score, dir, dir_count, path] = GetMin();
        SetC(pos, '#', in2);
        AddNew(pos, score, dir, dir_count, path);
    }

    LL result = 9999;
    for(auto m:matrix[endPos]){
        for(auto v: m.second){
            if(v<result) result = v;
        }
    }
    return result;
}

auto count2() {
    LL endPos = GetPos(X-1, Y-1);

    FOR(i, X*Y){
        Point map;
        map[Dir::Left ] = VECI{999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999};
        map[Dir::Right] = VECI{999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999};
        map[Dir::Up   ] = VECI{999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999};
        map[Dir::Down ] = VECI{999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999,999999999};
        matrix.push_back(map);
    }

    queue.emplace_back(0, 0, Dir::None, 0, VECI{0});

    for(LL i = 0;!queue.empty();++i){
        auto [pos, score, dir, dir_count, path] = GetMin();
        SetC(pos, '#', in2);
        AddNew2(pos, score, dir, dir_count, path);
        // P(i);
        // P_VECV(queue);
    }

    LL result = 9999;
    for(auto m:matrix[endPos]){
        for(auto v: m.second){
            if(v<result) result = v;
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    // score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
