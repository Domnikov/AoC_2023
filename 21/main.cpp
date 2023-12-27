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
    FOR(i, N){
        step(elfs);
    }
    auto in2 = in;
    result = elfs.size();
    return result;
}

struct CachedField{
    bool even;
    std::vector<std::pair<LL, std::set<Elf>>> childs;
};

std::map<std::set<Elf>, CachedField> cache;

LL Do(std::set<Elf>& elfs, LL N){
    std::set<Elf> prev;
    std::set<Elf> preprev;
    for ( LL i = N; i > 0; --i) {
        std::exchange(preprev, std::exchange(prev, std::exchange(elfs, {})));
        for(auto& org:prev){
            if((org.row - 1) >= 0                       && in[org.row - 1][org.col    ] != '#') {elfs.emplace(org.row - 1, org.col    );}
            if((org.row + 1) <  R                       && in[org.row + 1][org.col    ] != '#') {elfs.emplace(org.row + 1, org.col    );}
            if(                      (org.col - 1) >= 0 && in[org.row    ][org.col - 1] != '#') {elfs.emplace(org.row    , org.col - 1);}
            if(                      (org.col + 1) <  C && in[org.row    ][org.col + 1] != '#') {elfs.emplace(org.row    , org.col + 1);}
        }
        if(elfs == preprev) {
            return i%2 ? elfs.size() : prev.size();
        }
    }
    return elfs.size();
}

auto count2() {
    LL result = 0;
    std::set<Elf> elfs{GetFirst()};

    LL N = 6;
    // LL N = 26501365;
    result = Do(elfs, N);

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
