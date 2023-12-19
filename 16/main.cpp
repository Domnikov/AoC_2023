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
std::map<LL, LL> tiles1;

enum class Dir {
    None = 0,
    Left = 0x1,
    Right = 0x10,
    Up = 0x100,
    Down = 0x1000,
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
    return pos / Y;
}

LL GetPos(LL x, LL y) {
    return y*X + x;
}

bool isLeft (LL d) { return d & (LL)Dir::Left ; }
bool isRight(LL d) { return d & (LL)Dir::Right; }
bool isUp   (LL d) { return d & (LL)Dir::Up   ; }
bool isDown (LL d) { return d & (LL)Dir::Down ; }

bool WasDirection(Dir d, LL pos) {
    switch(d) {
        case Dir::None : return false;
        case Dir::Left : return isLeft (pos);
        case Dir::Right: return isRight(pos);
        case Dir::Up   : return isUp   (pos);
        case Dir::Down : return isDown (pos);
    }
    P_LINE;
    exit(1);
}

void AddLeft (LL pos) { if(!tiles1.count(pos)){tiles1[pos] = 0;} tiles1[pos] |= (LL)Dir::Left ; }
void AddRight(LL pos) { if(!tiles1.count(pos)){tiles1[pos] = 0;} tiles1[pos] |= (LL)Dir::Right; }
void AddUp   (LL pos) { if(!tiles1.count(pos)){tiles1[pos] = 0;} tiles1[pos] |= (LL)Dir::Up   ; }
void AddDown (LL pos) { if(!tiles1.count(pos)){tiles1[pos] = 0;} tiles1[pos] |= (LL)Dir::Down ; }

void MarkDirection(Dir d, LL pos) {
    switch(d) {
        case Dir::None :                break;
        case Dir::Left : AddLeft (pos); break;
        case Dir::Right: AddRight(pos); break;
        case Dir::Up   : AddUp   (pos); break;
        case Dir::Down : AddDown (pos); break;
        default:
            P_LINE;
            exit(1);
    }
}

LL ToLeft (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x == 0) { throw S("x < 0"); } return GetPos(x-1, y  ); }
LL ToRight(LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( x >= X) { throw S("x > X"); } return GetPos(x+1, y  ); }
LL ToUp   (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y == 0) { throw S("y < 0"); } return GetPos(x  , y-1); }
LL ToDown (LL pos) { LL x = GetX(pos); LL y = GetY(pos); if( y >= Y) { throw S("y > Y"); } return GetPos(x  , y+1); }

char GetC(LL pos){
    return in[GetY(pos)][GetX(pos)];
}

LL Move(Dir d, LL pos) {
    switch(d) {
        case Dir::None : throw(S("Not a direction"));
        case Dir::Left : return ToLeft (pos);
        case Dir::Right: return ToRight(pos);
        case Dir::Up   : return ToUp   (pos);
        case Dir::Down : return ToDown (pos);
    }
    P_LINE;
    exit(1);
}

Dir CheckDirection(Dir d, LL pos) {
        // switch(GetC(newPos)){
        //     case '-':
        // }
    return d;
}

void Beam(Dir d, LL pos) {
    // do {
        if(WasDirection(d, pos)) {
            P(d, std::make_pair(GetX(pos), GetY(pos)), "Duplicated. Exit");
            return;
        }
        MarkDirection(d, pos);
        LL newPos = 0;
        try{
            newPos = Move(d, pos);
        } catch(S err) {
            P(d, std::make_pair(GetX(pos), GetY(pos)), err, "Outside. Exit");
            return;
        }
        d = CheckDirection(d, pos);
    // } while (true);
}

void Print(){
    P_RR("\n");
    FOR(y, Y){
        FOR(x, X){
            if(tiles1.count(GetPos(x,y))) {
                P_RR("#");
            } else {
                P_RR(".");
            }
        }
        P_RR("\n");
    }
}

LL count1() {
    Beam(Dir::Right, 0);

    Print();

    return tiles1.size();
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
