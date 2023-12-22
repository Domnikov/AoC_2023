#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <cassert>
#include <queue>
#include <list>

auto in = getInput();
LL R = 394;
LL C = 349;


VECS field;

struct Point{
    LL row;
    LL col;
};

bool operator==(Point p1, Point p2){
    return p1.row == p2.row && p1.col == p2.col;
}

std::ostream& operator<<(std::ostream& s, Point p){
    s<<'['<<p.row<<','<<p.col<<']';
    return s;
}

struct Polygon {
    void AddPoint(LL x, LL y){
        AddPoint(Point{x, y});
    }

    void AddPoint(Point p) {
        if(std::find(BE(points), p) == points.end()){
            points.push_back(p);
        }
    }

    LL GetArea() {
        assert(points.size() > 2);
        LL result = 0;
        auto [xf, yf] = points[0];
        auto [xl, yl] = points[points.size()-1];
        LL pos = xl*yf;
        for(size_t i = 1; i < points.size(); i+=1){
            auto [x1, y1] = points[i-1];
            auto [x2, y2] = points[i];
            pos += x1*y2;
        }
        LL neg = xf*yl;
        for(size_t i = 1; i < points.size(); i+=1){
            auto [x1, y1] = points[i-1];
            auto [x2, y2] = points[i];
            neg += x2*y1;
        }
        return labs(pos-neg)/2;
    }

    LL GetBorderArea() {
        assert(points.size() > 2);
        LL counter = 1;
        for(LL i = 1; i < points.size(); ++i){
            Point p1 = points[i-1];
            Point p2 = points[i];
            counter += labs(p1.row-p2.row) + labs(p1.col-p2.col);
        }
        return counter;
    }

    LL GetFullArea(){
        return GetInner() + GetBorderArea();
    }

    LL GetInner() {
        LL Pinside = GetArea() + 1 - points.size()/2;
        return Pinside;
    }

    std::vector<Point> points;
};

Point Go(char c, LL num, Point point){
    switch(c){
        case 'R':
            point.col+=num;
            break;
        case 'L':
            point.col-=num;
            break;
        case 'U':
            point.row-=num;
            break;
        case 'D':
            point.row+=num;
            break;
    }
    P(point);
    assert(point.row >= 0);
    assert(point.col >= 0);
    assert(point.row < R);
    assert(point.col < C);
    return point;
}

void mark(VECS& field, Point p1, Point p2){
    assert(p1.row == p2.row || p1.col == p2.col);
    for(LL r = std::min(p1.row, p2.row); r <= std::max(p1.row, p2.row); ++r){
        field[r][p1.col] = '#';
    }
    for(LL c = std::min(p1.col, p2.col); c <= std::max(p1.col, p2.col); ++c){
        field[p1.row][c] = '#';
    }
}

auto count1() {
    LL result = 0;
    field.clear();
    FOR(n, R) {
        field.push_back(S(C, '.'));
    }
    Point p0{209,132};
    Polygon pol;
    pol.AddPoint(p0);

    for(const auto& s: in){
        auto vec = splitStr(s, ' ');
        char dir = vec[0][0];
        LL num = stoi(vec[1]);
        S color = vec[2];

        Point p2 = Go(dir, num, p0);
        mark(field, p0, p2);
        p0 = p2;
        pol.AddPoint(p0);
    }

    P_VECV(field);

    Polygon Pol;

    Pol.AddPoint(1,1);
    Pol.AddPoint(1,3);
    Pol.AddPoint(3,3);
    Pol.AddPoint(3,1);

    P(Pol.GetArea());
    P(Pol.GetInner());
    P(Pol.GetArea() - Pol.GetInner());
    P(Pol.GetBorderArea());
    P(Pol.GetFullArea());



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
