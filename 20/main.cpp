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

LL outputH = 0;
LL outputL = 0;

void Set(S from, S to, bool level, Ptype& dst) {
    if(to == "broadcaster") {
        dst[to] = level;
    } else if(ffmod.count(to)) {
        dst[to] = level;
    } else if(cjmod.count(to)) {
        dst[to+'|'+from] = level;
    } else if(to == "output" || to == "rx"){
        if(level) {
            // P_RR("outputH\n");
            ++outputH;
        } else {
            // P_RR("outputL\n");
            ++outputL;
        }
    } else {
        P(to);
        P_LINE;
        exit(1);
    }
}

std::pair<LL,LL> Push(Ptype& mod) {
    std::pair<LL,LL> p{0,0};
    Ptype copy;
    for(auto& m:mod){
        p.first += m.second;
        p.second += !m.second;
        // P(m, p);
        // copy.insert(m);
        auto vec = splitStr(m.first, '|');
        if(m.first == "broadcaster") {
            for(const auto& out: bcast) {
                levels["broadcaster"] = m.second;
                Set(m.first, out, m.second, copy);
            }
        } else if(ffmod.count(m.first)) {
            bool level = levels[m.first];
            if(!m.second) {
                levels[m.first] = !level;
                for(const auto& out: ffmod[m.first]) {
                    Set(m.first, out, !level, copy);
                }
            }
        } else if(cjmod.count(vec[0])) {
            bool isAllHigh = true;
            levels[m.first] = m.second;
            // P_MAPV(levels);
            for(const auto& ii:ffmod){
                if (!isAllHigh) break;
                for(const auto& iii:ii.second) {
                    if(iii == vec[0]) {
                        if(!levels[vec[0]+'|'+ii.first]) {
                            isAllHigh = false;
                            break;
                        }
                    }
                }
            }
            for(const auto& ii:cjmod){
                if (!isAllHigh) break;
                for(const auto& iii:ii.second) {
                    if(iii == vec[0]) {
                        if(!levels[vec[0]+'|'+ii.first]) {
                            isAllHigh = false;
                            break;
                        }
                    }
                }
            }
            // P(isAllHigh);
            for(const auto& out: cjmod[vec[0]]) {
                Set(vec[0], out, !isAllHigh, copy);
            }
        } else {
            P_LINE;
            exit(1);
        }
    }
    // P_MAPV(copy);
    mod = copy;

    if(mod.size()) {
        std::pair<LL,LL> recRus = Push(mod);
        p.first += recRus.first;
        p.second += recRus.second;
    }
    return p;
}

auto count1() {
    LL result = 0;
    std::pair<LL,LL> pair{0,0};
    FOR(i, 1000LL) {
        outputH = 0;
        outputL = 0;
        // P_RR("%lld\n", i);
        Ptype mod;
        mod["broadcaster"] = false;
        auto local = Push(mod);
        pair.first += local.first;
        pair.second += local.second;
        pair.first += outputH;
        pair.second += outputL;
        // P(local, pair);
    }
    result = pair.first*pair.second;
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

    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
