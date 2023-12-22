#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

std::map<S, VECSS> map;
using Work = std::map<char, LL>;
std::vector<Work> work;

bool Process(const Work& w){
    return true;
}

auto count1() {
    LL result = 0;
    bool iswork = false;
    FOR(i, in.size()) {
        S s = in[i];
        if(s.empty()){
            iswork = true;
        } else if(iswork){
            s.erase(0,1);
            s.erase(s.size()-1);
            auto v = splitStr(s, ',');
            decltype(work)::value_type mm;
            for(auto m:v){
                char c = m[0];
                m.erase(0,2);
                mm[c] = stoll(m);
            }
            work.push_back(mm);
        } else {
            auto v1 = splitStr(s, '{');
            S name = v1[0];
            VECSS cond;
            v1[1].erase(v1[1].size()-1);
            auto v2 = splitStr(v1[1], ',');
            for(auto vs:v2){
                auto v3 = splitStr(vs,':');
                cond.push_back(v3);
            }
            map[name] = cond;
        }
    }

    P_MAPV(map);
    for(auto v:work){
        P_MAPV(v);
    }
#if 0
        crn: [[x>2662;A];[R]]
        gd: [[a>3333;R];[R]]
        hdj: [[m>838;A];[pv]]
        in: [[s<1351;px];[qqz]]
        lnx: [[m>1548;A];[A]]
        pv: [[a>1716;R];[A]]
        px: [[a<2006;qkq];[m>2090;A];[rfg]]
        qkq: [[x<1416;A];[crn]]
        qqz: [[s>2770;qs];[m<1801;hdj];[R]]
        qs: [[s>3448;A];[lnx]]
        rfg: [[s<537;gd];[x>2440;R];[A]]
#endif

    for(const auto& w:work){
        if(Process(w)){
            ;
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
