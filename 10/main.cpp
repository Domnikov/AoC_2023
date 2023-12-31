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

LL Up(LL pos){
    auto x = X(pos);
    auto y = Y(pos);
    return N(x, y-1);
}

LL Down(LL pos){
    auto x = X(pos);
    auto y = Y(pos);
    return N(x, y+1);
}

LL Left(LL pos){
    auto x = X(pos);
    auto y = Y(pos);
    return N(x-1, y);
}

LL Right(LL pos){
    auto x = X(pos);
    auto y = Y(pos);
    return N(x+1, y);
}

VECI GetConnections(LL pos){
    // P(pos, Get(pos));
    switch(Get(pos)){
        case '|':
            return {Up(pos), Down(pos)};
        case '-':
            return {Left(pos), Right(pos)};
        case 'L':
            return {Up(pos), Right(pos)};
        case 'J':
            return {Up(pos), Left(pos)};
        case '7':
            return {Left(pos), Down(pos)};
        case 'F':
            return {Right(pos), Down(pos)};
    }
    return {};
}

bool isPipe(LL pos){
    switch(Get(pos)){
        case '|':
        case '-':
        case 'L':
        case 'J':
        case '7':
        case 'F':
            return true;
        default:
            return false;
    }
}

void GetNext(LL& pos, LL n){
    LL nextPos;
    auto con = GetConnections(pos);
    if(isPipe(con[0]) && !isPipe(con[1])) nextPos = con[0];
    else if(isPipe(con[1]) && !isPipe(con[0])) nextPos = con[1];
    else {P_LINE; exit(1);}
    Set(pos, n);
    pos = nextPos;
}

VECPLL P;
LL points;

auto count1() {
    LL result = 1;
    auto start = findStart();
    auto l = Left(start);
    auto r = Right(start);
    auto u = Up(start);
    auto d = Down(start);
    auto conl = GetConnections(l);
    auto conr = GetConnections(r);
    auto conu = GetConnections(u);
    auto cond = GetConnections(d);
    VECI conStart;
    if(!conl.empty() && (conl[0] == start || conl[1] == start)) {conStart.push_back(l);}
    if(!conr.empty() && (conr[0] == start || conr[1] == start)) {conStart.push_back(r);}
    if(!conu.empty() && (conu[0] == start || conu[1] == start)) {conStart.push_back(u);}
    if(!cond.empty() && (cond[0] == start || cond[1] == start)) {conStart.push_back(d);}

    if(conStart.size() != 2){
        P_VEC(conStart);
        P_LINE;
        exit(1);
    }

    auto p1 = conStart[0];
    auto p2 = conStart[1];
    Set(start, 0);
    std::deque<LL> DP;
    DP.push_back(start);

    while (p1 != p2){
        ++result;
        DP.push_front(p1);
        DP.push_back(p2);
        GetNext(p1, 0);
        GetNext(p2, 0);
    }
    char c2 = Get(p2);
    DP.push_back(p2);
    points = DP.size();
    for(auto pos:DP){
        char c2 = Get(pos);
        if(c2 != '|' && c2 != '-')P.emplace_back(X(pos), Y(pos));
    }

    return result;
}

auto count2(){
    LL result = 0;
    auto [xf, yf] = P[0];
    auto [xl, yl] = P[P.size()-1];
    LL pos = xl*yf;
    for(size_t i = 1; i < P.size(); i+=1){
        auto [x1, y1] = P[i-1];
        auto [x2, y2] = P[i];
        pos += x1*y2;
    }
    LL neg = xf*yl;
    for(size_t i = 1; i < P.size(); i+=1){
        auto [x1, y1] = P[i-1];
        auto [x2, y2] = P[i];
        neg += x2*y1;
    }
    auto A = labs(pos-neg)/2;
    P(A, points);
    LL Pinside = A + 1 - points/2;
    return Pinside;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    in = getInput();
    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
