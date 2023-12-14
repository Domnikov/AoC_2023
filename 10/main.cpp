#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL Y(LL pos){
    return pos/in[0].size();
}

LL X(LL pos){
    return pos%in[0].size();
}

LL N(LL x, LL y){
    return y*in[0].size() + x;
}

char Get(LL pos){
    return in[Y(pos)][X(pos)];
}

void Set(LL pos, LL n){
    in[Y(pos)][X(pos)] = n;
}

LL findStart(){
    FOR(i, in.size()*in[0].size()){
        if(Get(i) == 'S'){
            return i;
        }
    }
    P_LINE;
    exit(1);
}

LL Up(LL n){
    auto x = X(n);
    auto y = Y(n);
    return N(x, y+1);
}

LL Down(LL n){
    auto x = X(n);
    auto y = Y(n);
    return N(x, y-1);
}

LL Left(LL n){
    auto x = X(n);
    auto y = Y(n);
    return N(x-1, y);
}

LL Right(LL n){
    auto x = X(n);
    auto y = Y(n);
    return N(x+1, y);
}

VECI GetConnections(LL n){
    // P(n, Get(n));
    switch(Get(n)){
        case '|':
            return {Up(n), Down(n)};
        case '-':
            return {Left(n), Right(n)};
        case 'L':
            return {Up(n), Right(n)};
        case 'J':
            return {Up(n), Left(n)};
        case '7':
            return {Left(n), Down(n)};
        case 'F':
            return {Right(n), Down(n)};
    }
    return {};
}

void GetNext(LL& pos, LL n){
    LL nextPos;
    Set(pos, n);
    pos = nextPos;
}

auto count1() {
    LL result = 0;
    auto start = findStart();
    auto l = Left(start);
    auto r = Right(start);
    auto u = Up(start);
    auto d = Down(start);
    auto conl = GetConnections(l);
    auto conr = GetConnections(r);
    auto conu = GetConnections(u);
    auto cond = GetConnections(d);
    P(start);
    P_VEC(conl);
    P_VEC(conr);
    P_VEC(conu);
    P_VEC(cond);
    VECI conStart;
    if(!conl.empty() && (conl[0] == start || conl[1] == start)) {P_LINE;conStart.push_back(l);}
    if(!conr.empty() && (conr[0] == start || conr[1] == start)) {P_LINE;conStart.push_back(r);}
    if(!conu.empty() && (conu[0] == start || conu[1] == start)) {P_LINE;conStart.push_back(u);}
    if(!cond.empty() && (cond[0] == start || cond[1] == start)) {P_LINE;conStart.push_back(d);}

    P_VEC(conStart);
    if(conStart.size() != 2){
        P_LINE;
        exit(1);
    }

    auto p1 = conStart[0];
    auto p2 = conStart[1];

    P(start, p1, p2);

    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count1();
    P_RR("Part2: %lld\n", score);
    return 0;
}
