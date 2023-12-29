#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
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

        double x1=vecp[0];
        double y1=vecp[1];

        double x2=x1+vecv[0];
        double y2=y1+vecv[1];

        a = y1 - y2;
        b = x2 - x1;
        c = x1*y2 - x2*y1;

    }

    bool IsParal(const Line2d& other) {
        return ((a / other.a) == (b / other.b));
    }

    std::pair<double,double> intersect(const Line2d& other) {
        double x, y;
        double det = a * other.b - other.a * b;
        x = (b * other.c - other.b * c) / det;
        y = (other.a * c - a * other.c) / det;

        return {x,y};
    }

    double a;
    double b;
    double c;
};

auto count1() {
    LL result = 0;
    std::vector<Line2d> lines;
    std::transform(BE(in), std::back_inserter(lines), [](const auto& s){return Line2d(s);});

    std::vector<std::pair<Line2d, Line2d>> crossingLines;

    FOR(i, lines.size()){
        for(LL j = i+1; j < lines.size();++j) {
            if(lines[i].IsParal(lines[j]) == false) {
                crossingLines.emplace_back(lines[i], lines[j]);
            }
        }
    }

    return result = crossingLines.size();
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
