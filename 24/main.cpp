#ifdef TEST
#include "in_test.hpp"
long double L = 7;
long double H = 21;
#else
#include "in.hpp"
long double L = 200000000000000;
long double H = 400000000000000;
#endif

#include <cassert>
#include <queue>
#include <list>

auto in = getInput();

#if 0
struct Line2d{
    Line2d(const S& str){
        auto vecs = splitStr(str, '@');
        assert(vecs.size() == 2);
        auto vecp = vecsToVeci(splitStr(vecs[0], ','));
        auto vecv = vecsToVeci(splitStr(vecs[1], ','));

        assert(vecp.size() == 3);
        assert(vecv.size() == 3);

        x=vecp[0];
        y=vecp[1];

        vx=vecv[0];
        vy=vecv[1];

        long double x2=x+vx;
        long double y2=y+vy;

        a = y - y2;
        b = x2 - x;
        c = x*y2 - x2*y;

    }

    bool IsParal(const Line2d& other) const {
        return ((a / other.a) == (b / other.b));
    }

    bool ISCrossInFuture(const Line2d& other) const {
        if(IsParal(other)){
            return false;
        }
        auto [cx, cy] = GetCP(other);
        auto dx = cx-x;
        auto dxOther = cx-other.x;
        bool result1 = ((dx/vx) >= -0.01);
        bool result2 = ((dxOther/other.vx) >= -0.01);
        bool result = result1 && result2;
        return result;
    }

    std::pair<long double,long double> GetCP(const Line2d& other) const {
        long double x, y;
        long double det = a * other.b - other.a * b;
        x = (b * other.c - other.b * c) / det;
        y = (other.a * c - a * other.c) / det;

        return {x,y};
    }

    long double a;
    long double b;
    long double c;
    long double x;
    long double y;
    long double vx;
    long double vy;
};

auto count1() {
    LL result = 0;
    std::vector<Line2d> lines;
    std::transform(BE(in), std::back_inserter(lines), [](const auto& s){return Line2d(s);});

    std::vector<std::pair<Line2d, Line2d>> crossingLines;

    FOR(i, lines.size()){
        for(LL j = i+1; j < lines.size();++j) {
            if(lines[i].ISCrossInFuture(lines[j])) {
                crossingLines.emplace_back(lines[i], lines[j]);
            }
        }
    }

    for(const auto& pair : crossingLines) {
        auto [x,y] = pair.first.GetCP(pair.second);
        // P(x, y);
        if( (L-0.01) <= x && x <= (H+0.01) && (L-0.01) <= y && y <= (H+0.01) ) {
            result ++;
        }
    }

    return result;
}
#endif

struct Line4d {
    Line4d(const S& str){
        auto vecs = splitStr(str, '@');
        assert(vecs.size() == 2);
        auto vecp = vecsToVeci(splitStr(vecs[0], ','));
        auto vecv = vecsToVeci(splitStr(vecs[1], ','));

        assert(vecp.size() == 3);
        assert(vecv.size() == 3);

        coord = vecp;
        velos = vecv;
    }

    VECI coord;
    VECI velos;
};

auto count2() {
    LL result = 0;
    std::vector<Line4d> lines;
    std::transform(BE(in), std::back_inserter(lines), [](const auto& s){return Line4d(s);});

    FOR(i, lines.size()){
        auto& l = lines[i];
        for(LL j = i+1; j < lines.size();++j) {
            for(LL t = 2; t < 1000; ++t) {
                FOR(k, lines.size()){
                    if( k != i && k != j) {
                        result++;
                    }
                }
                P(t);
            }
            P(j);
        }
        P(i);
        // V0 = (x1 - C2 - T*V2) / ( 1 - T)
    }
#if 0

x1 = V1*1 + C1

x0 = V0*T + (x1-V0)
x2 = V2*T + C2

0 = T(V0-V2) + x1 - V0 - C2

T(V2 - V0) + V0 = x1 - C2

T*V2 - T*V0 + V0 = x1 - C2

(1-T)*V0 = (x1 - C2 - T*V2)

 ->   V0 = (x1 - C2 - T*V2) / ( 1 - T)

V0 = (21 - 18 + 3) / (1-3) = 6 / -2

V0 = (C2 - x1 + T*V2) / (T - 1)

V0 = (18 - 21 - 3) / (-2) = 3

1 = V0/V2 + (x1-V0)

1 = v0/V2 + x1 - V0

(1-x1) = V0((1-V2)/V2)

V0 = (V2 * (1-x1))/(1-V1)

#endif

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
