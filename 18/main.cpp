#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <cassert>
#include <queue>
#include <list>

auto in = getInput();
LL R = 400;
LL C = 355;


VECS field;

struct PP{
    LL row;
    LL col;
};

std::ostream& operator<<(std::ostream& s, PP p){
    s<<'['<<p.row<<','<<p.col<<']';
    return s;
}

PP Go(char c, LL num, PP point){
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

void mark(VECS& field, PP p1, PP p2){
    P(p1, p2);
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
    PP p0{210,135};
    std::vector<PP> points;
    points.push_back(p0);

    for(const auto& s: in){
        auto vec = splitStr(s, ' ');
        char dir = vec[0][0];
        LL num = stoi(vec[1]);
        S color = vec[2];

        PP p2 = Go(dir, num, p0);
        mark(field, p0, p2);
        p0 = p2;
        points.push_back(p0);
    }

    P_VECV(field);

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
