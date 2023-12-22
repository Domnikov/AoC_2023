#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();
std::map<S, VECS> ffmod;
std::map<S, VECS> cjmod;
VECS bcast;
using Ptype = std::map<S, bool>;

Ptype levels;

void Set(S from, S to, bool level, Ptype& dst) {
    if(to == "broadcaster") {
        dst[to] = level;
    } else if(ffmod.count(to)) {
        dst[to] = level;
    } else if(cjmod.count(to)) {
        dst[to+'|'+from] = level;
    } else {
        P_LINE;
        exit(1);
    }
}

LL Push(Ptype& mod) {
    Ptype copy;
    for(auto& m:mod){
        // copy.insert(m);
        auto vec = splitStr(m.first, '|');
        if(m.first == "broadcaster") {
            P(m, __LINE__);
            for(const auto& out: bcast) {
                levels["broadcast"] = m.second;
                Set(m.first, out, m.second, copy);
            }
        } else if(ffmod.count(m.first)) {
            P(m, __LINE__);
            bool level = levels[m.first];
            if(!m.second) {
                levels[m.first] = !level;
                for(const auto& out: ffmod[m.first]) {
                    Set(m.first, out, !level, copy);
                }
            }
        } else if(cjmod.count(vec[0])) {
            P(m, __LINE__);
            bool isAllHigh = true;
            levels[m.first] = m.second;
            P_MAPV(levels);
            for(const auto& ii:cjmod){
                P(ii);
                for(const auto& iii:ii.second) {
                    P(iii, vec[0]);
                    if(iii == vec[0]) {
                        if(!levels[vec[0]+'|'+iii]) {
                            isAllHigh = false;
                            break;
                        }
                    }
                }
                if (!isAllHigh) break;
            }
            P(isAllHigh);
            for(const auto& out: cjmod[vec[0]]) {
                Set(vec[0], out, !isAllHigh, copy);
            }
        } else {
            P_LINE;
            exit(1);
        }
    }
    P_MAPV(copy);
    mod = copy;

    if(mod.size())
        return Push(mod);
    return 0;
}

auto count1() {
    LL result = 0;
    Ptype mod;
    mod["broadcaster"] = false;
    result = Push(mod);
    return result;
}

auto count2() {
    LL result = 0;

    return result;
}

int main(int argc, char** argv)
{
    for(const auto& l: in){
        auto v = splitStr(l, '>');
        auto name = splitStr(v[0], ' ')[0];
        auto outs = splitStr(v[1], ',');
        char type = name[0];
        if(name == "broadcaster") {
            bcast = outs;
            levels[name] = false;
        } else if(type == '%') {
            name.erase(0,1);
            ffmod[name] = outs;
            levels[name] = false;
        } else if(type == '&') {
            name.erase(0,1);
            cjmod[name] = outs;
        } else {
            P(type);
            P_LINE;
            exit(1);
        }
    }

    for(auto cj: cjmod){
        for(auto out: cj.second){
            if(cjmod.count(out)){
                levels[out+'|'+cj.first] = false;
            }
        }
    }

    for(auto cj: ffmod){
        for(auto out: cj.second){
            if(cjmod.count(out)){
                levels[out+'|'+cj.first] = false;
            }
        }
    }

    P_MAPV(levels);

    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
