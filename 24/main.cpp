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
#include <cmath>
#include <queue>
#include <list>
#include <limits>

auto in = getInput();

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

    Line2d(const VECI& vecp, const VECI& vecv){
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
    std::map<std::vector<std::pair<LL,LL>>, std::pair<LL,LL>> map[3];
    FOR(n, 3)
    // LL n = 1;
    {
        FOR(i, lines.size()){
            auto& l = lines[i];
            // P(l.coord, l.velos);
            LL x1 = l.coord[n] + l.velos[n];
            FOR(j, lines.size()) {
                if(i == j) {
                    continue;
                }
                // P(lines[j].coord, lines[j].velos);
                LL c2 = lines[j].coord[n];
                LL v2 = lines[j].velos[n];
                for(LL t = 2; t < 700; ++t) {
                    long double Vtmp1 = x1 - c2 - t*v2;
                    long double Vtmp2 = 1-t;
                    auto V0f = Vtmp1 / Vtmp2;
                    auto C0f = x1 - V0f;
                    LL V0 = V0f;
                    LL C0 = C0f;
                    if((C0f - C0) > 0.01) {
                        continue;
                    }
                    if((V0f - V0) > 0.01) {
                        continue;
                    }
                    // P(t, C0, V0);
                    bool found = true;
                    std::vector<std::pair<LL,LL>> vec;
                    FOR(k, lines.size()){
                        LL Ck = lines[k].coord[n];
                        LL Vk = lines[k].velos[n];
                        if (Ck == C0 && Vk == V0) {
                            P(C0, V0, Ck, Vk, t, lines[k].coord);
                            vec.emplace_back(k, 5);
                        } else {
                            auto cp = Line2d({C0, 0, 0}, {V0, 1, 0}).GetCP(Line2d{{Ck, 0, 0},{Vk, 1, 0}});
                            // P(cp, C0, V0, Ck, Vk, t, lines[k].coord);
                            if(std::isnan(cp.second) || cp.second == std::numeric_limits<long double>::infinity() || cp.second < 1) {
                                found = false;
                                break;
                            }
                            vec.emplace_back(k, cp.second);
                        }
                    }
                    if(found) {
                        // P(found, t, C0, V0);
                        map[n][vec] = std::make_pair(C0, V0);
                    }
                }
            }
        }
    }
    // P_MAPV(map[0]);
    // P_MAPV(map[1]);
    // P_MAPV(map[2]);
    for(const auto& m0:map[0]) {
        if(map[1].count(m0.first) && map[2].count(m0.first)){
            P(m0.second, map[1][m0.first], map[2][m0.first]);
        }
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


X0 = V0*T + C0
Xj = Vj*T + Cj

V0*T + C0 = Vj*T + Cj

T = (Cj - C0) / (V0 - Vj)
T = (19 - 24) / (-3 - -2) = -5 / (-3 + 2)
t = 3;  a = 22; b = -1; Ck = 19;        x1 = 21;        C0 = 24;        V0 = -3;        Vk = -2;        locT = -22

#endif

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
