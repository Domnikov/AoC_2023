#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL R = in.size();
LL C = in[0].size();

class Elf {
  public:
    Elf(LL r, LL c) {
        static LL counter = 0;
        id= counter++;
        row=r;
        col=c;
    }
    LL id;
    LL row;
    LL col;
};

std::ostream& operator<<(std::ostream& os, const Elf& me) {
    os<<"Elf("<<me.id<<",["<<me.row<<","<<me.col<<"])";
    return os;
}

bool operator<(const Elf& lhs, const Elf& rhs) {
    LL s1 = lhs.row*1000+lhs.col;
    LL s2 = rhs.row*1000+rhs.col;
    return s1 < s2;
}

bool operator==(const Elf& lhs, const Elf& rhs) {
    LL s1 = lhs.row*1000+lhs.col;
    LL s2 = rhs.row*1000+rhs.col;
    return s1 == s2;
}

Elf GetFirst(){
    FOR(row, in.size()){
        FOR(col, in[row].size()){
            if(in[row][col] == 'S'){
                return Elf{(LL)row, (LL)col};
            }
        }
    }
    exit(1);
}

VECS GetField(std::set<Elf> elfs) {
    auto in2 = in;
    for(const auto& e:elfs){
        in2[e.row][e.col] = 'O';
    }
    return in2;
}

std::ostream& operator<<(std::ostream& os, const std::set<Elf>& elfs) {
    P_VECV(GetField(elfs));
    return os;
}

void step(std::set<Elf>& elfs){
    std::set<Elf> copy;
    for(auto& org:elfs){
        if((org.row - 1) >= 0                       && in[org.row - 1][org.col    ] != '#') {copy.emplace(org.row - 1, org.col    );}
        if((org.row + 1) <  R                       && in[org.row + 1][org.col    ] != '#') {copy.emplace(org.row + 1, org.col    );}
        if(                      (org.col - 1) >= 0 && in[org.row    ][org.col - 1] != '#') {copy.emplace(org.row    , org.col - 1);}
        if(                      (org.col + 1) <  C && in[org.row    ][org.col + 1] != '#') {copy.emplace(org.row    , org.col + 1);}
    }
    elfs.swap(copy);
}

auto count1() {
    LL result = 0;
    std::set<Elf> elfs{GetFirst()};

    LL N = 64;
    LL counter = 1;
    FOR(i, N){
        step(elfs);
        if(i > counter){
            // P(counter);
            counter *= 10;
        }
    }
    auto in2 = in;
    result = elfs.size();
    // P(elfs);
    return result;
}

struct Cache{
    VECI next{9, -1};
    VECI data;
};

enum SIDES{LT, RT, UP, DN, LU, LD, RU, RD, CT};
std::vector<Elf> Generate(Elf init, Cache& result){
    P(init, result.next);
    std::vector<Elf> nxt;
    nxt.emplace_back(-1,-1);
    nxt.emplace_back(-1,-1);
    nxt.emplace_back(-1,-1);
    nxt.emplace_back(-1,-1);
    std::set<Elf> cur{init};
    std::set<Elf> prev;
    std::set<Elf> preprev;
    FOR(i, 10000){
        result.data.push_back(cur.size());
        std::exchange(preprev, std::exchange(prev, std::exchange(cur, {})));
        for(auto& org:prev){
            {LL nr = (org.row - 1); LL nc = (org.col); if(nr >= 0) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(nxt[DN].row == -1){result.next[DN] = i;nxt[DN].row =R-1; nxt[DN].col = nc;}}}
            {LL nr = (org.row + 1); LL nc = (org.col); if(nr <  R) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(nxt[UP].row == -1){result.next[UP] = i;nxt[UP].row =  0; nxt[UP].col = nc;}}}
            {LL nc = (org.col - 1); LL nr = (org.row); if(nc >= 0) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(nxt[RT].row == -1){result.next[RT] = i;nxt[RT].row = nr; nxt[RT].col =C-1;}}}
            {LL nc = (org.col + 1); LL nr = (org.row); if(nc <  C) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(nxt[LT].row == -1){result.next[LT] = i;nxt[LT].row = nr; nxt[LT].col =  0;}}}
        }
        // P(cur.size(), cur);
        if(cur == preprev) {
            // P(cur);
            // P(prev);
            return nxt;
        }
    }
    exit(1);
}

bool less(LL N, LL NR, LL NC, LL row, LL col) {
    LL r = llabs(NR - row);
    LL c = llabs(NC - col);
    return N*N > ((r*r) + (c*c));
}

auto count2() {
    LL result = 0;

    LL N = 10;
    // LL N = 26501365;
    auto first = GetFirst();

    std::vector<Cache> src;
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();
    src.emplace_back();

    std::vector<Elf> next = Generate(first, src[CT]);
    Generate(next[LT], src[LT]);
    Generate(next[RT], src[RT]);
    Generate(next[DN], src[DN]);
    Generate(next[UP], src[UP]);

    Generate(Elf{  0,  0}, src[LU]);
    Generate(Elf{R-1,  0}, src[LD]);
    Generate(Elf{  0,  0}, src[RU]);
    Generate(Elf{R-1,C-1}, src[RD]);


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
