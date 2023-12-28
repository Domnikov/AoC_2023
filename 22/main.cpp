#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include "cassert"
#include <queue>
#include <list>

auto in = getInput();

struct Brik {
    LL x1, y1, z1;
    LL x2, y2, z2;

    Brik(LL x1, LL y1, LL z1, LL x2, LL y2, LL z2)
    :x1{x1},x2{x2}, y1{y1},y2{y2}, z1{z1},z2{z2} {
        assert(x1<=x2);
        assert(y1<=y2);
        assert(z1<=z2);
    }
    Brik(VECI one, VECI two)
    :Brik(one[0], one[1], one[2], two[0], two[1], two[2]) {
    }
};

std::ostream& operator<<(std::ostream& os, const Brik& br){
    os<<"["<<br.x1<<","<<br.y1<<","<<br.z1<<","<<br.x2<<","<<br.y2<<","<<br.z2<<"]";
    return os;
}

bool operator<(const Brik& br1, const Brik& br2){
    if(br1.z1 != br2.z1) return br1.z1 < br2.z1;
    if(br1.z2 != br2.z2) return br1.z2 < br2.z2;
    if(br1.x1 != br2.x1) return br1.x1 < br2.x1;
    if(br1.x2 != br2.x2) return br1.x2 < br2.x2;
    if(br1.y1 != br2.y1) return br1.y1 < br2.y1;
    if(br1.y2 != br2.y2) return br1.y2 < br2.y2;
    P_LINE;
    exit(1);
}

std::vector<Brik> GetAllBriks(){
    std::vector<Brik> briks;
    for(const auto& s:in){
        auto vecAll = splitStr(s, '~');
        auto vec1 = vecsToVeci(splitStr(vecAll[0], ','));
        auto vec2 = vecsToVeci(splitStr(vecAll[1], ','));
        briks.emplace_back(vec1, vec2);
    }
    return briks;
}

bool MoveDownOne(std::set<LL>& used, Brik& brik){
    LL x1 = brik.x1;
    LL x2 = brik.x2;
    LL y1 = brik.y1;
    LL y2 = brik.y2;
    LL z1 = brik.z1-1;
    LL z2 = brik.z2-1;
    if(z1 < 2) return false;
    for(LL x = x1; x <= x2;x++)
        for(LL y = y1; y <= y2;y++)
            for(LL z = z1; z <= z2;z++){
                if(used.count(x*1000000+y*1000+z)) {
                    return false;
                }
            }
    brik.z1 = z1;
    brik.z2 = z2;
    return true;
}

void Fix(std::set<LL>& used, const Brik& brik){
    for(LL x = brik.x1; x <= brik.x2;x++)
        for(LL y = brik.y1; y <= brik.y2;y++)
            for(LL z = brik.z1; z <= brik.z2;z++){
                used.insert(x*1000000+y*1000+z);
            }
}

void MoveDownAll(std::vector<Brik>& briks) {
    std::set<LL> used;
    for(auto& b:briks){
        while(MoveDownOne(used, b)){}
        Fix(used, b);
    }

}

auto count1() {
    LL result = 0;
    auto briks = GetAllBriks();
    std::sort(BE(briks));
    P_VECV(briks);
    MoveDownAll(briks);
    std::sort(BE(briks));
    P_VECV(briks);
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
