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

LL Push(Ptype& mod) {
    Ptype copy;
    FOR(i,2){
        for(auto& m:mod){
            // copy.insert(m);
            if(m.first == "broadcaster") {
                for(const auto& out: bcast) {
                    levels["broadcast"] = m.second;
                    copy[out] = m.second;
                }
            } else if(ffmod.count(m.first)) {
                bool level = levels[m.first];
                if(!m.second) {
                    levels[m.first] = !level;
                    for(const auto& out: bcast) {
                        copy[out] = !level;
                    }
                }
            } else if(cjmod.count(m.first)) {
                bool level = levels[m.first];
                if(!m.second) {
                    levels[m.first] = !level;
                    for(const auto& out: bcast) {
                        copy[out] = !level;
                    }
                }
            } else {
                P_LINE;
                exit(1);
            }
        }
        mod = copy;
    }
    P_MAP(mod);
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
