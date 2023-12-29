#ifdef TEST
#include "in_test.hpp"
double L = 7;
double H = 21;
#else
#include "in.hpp"
double L = 200000000000000;
double H = 400000000000000;
#endif

#include <cassert>
#include <queue>
#include <list>

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

        double x2=x+vx;
        double y2=y+vy;

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
        if(!result) {
            P(cx, x, dx, vx, dxOther, other.x, other.vx, result1, result2);
        }
        return result;
    }

    std::pair<double,double> GetCP(const Line2d& other) const {
        double x, y;
        double det = a * other.b - other.a * b;
        x = (b * other.c - other.b * c) / det;
        y = (other.a * c - a * other.c) / det;

        return {x,y};
    }

    double a;
    double b;
    double c;
    double x;
    double y;
    double vx;
    double vy;
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
        if( L <= x && x <= H && L <= y && y <= H ) {
            result ++;
        }
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
