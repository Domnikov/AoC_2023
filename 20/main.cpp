#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();
/*
std::map<S, VECS> ffmod;
std::map<S, VECS> cjmod;
VECS bcast;
using Ptype = std::map<S, bool>;

Ptype levels;

LL outputH = 0;
LL outputL = 0;
LL counter = 0;

void Set(S from, S to, bool level, std::vector<std::pair<S,bool>>& dst) {
    if(to == "broadcaster") {
        dst.emplace_back(to, level);
    } else if(ffmod.count(to)) {
        dst.emplace_back(to, level);
    } else if(cjmod.count(to)) {
        dst.emplace_back(to+'|'+from, level);
    } else if(to == "output" || to == "rx"){
        if(level) {
            ++outputH;
        } else {
            ++outputL;
            P(counter);
            exit(1);
        }
    } else {
        P(to);
        P_LINE;
        exit(1);
    }
}

std::pair<LL,LL> Push(std::vector<std::pair<S,bool>>& mod) {
    std::pair<LL,LL> p{0,0};
    std::vector<std::pair<S,bool>> copy;
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
}*/

struct Node{
    virtual void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) = 0;
    virtual void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) = 0;

    std::vector<LL> levels;

    S name;

    std::vector<std::shared_ptr<Node>> ins;
    std::vector<std::shared_ptr<Node>> outs;
};

struct ffNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        P_RR("%s -%s-> %s\n", in_name.c_str(), level ? "high":"low", name.c_str());
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
        }
        if(!level) {
            levels[0] = !level;
        }
    }
    void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        if(!level) {
            for(auto& out:outs) {
                out->update(!level, name, cnt_pair);
            }
            for(auto& out:outs) {
                out->check(!level, name, cnt_pair);
            }
        }
    }
};

struct cjNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        P_RR("%s -%s-> %s\n", in_name.c_str(), level ? "high":"low", name.c_str());
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
        }
        FOR(i, levels.size()){
            if(ins[i]->name == in_name) {
                levels[i] = level;
                return;
            }
        }
    }
    void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        bool isAllHigh = true;
        FOR(i, levels.size()){
            if(!levels[i]) {
                isAllHigh = false;
                break;
            }
        }
        for(auto& out:outs) {
            out->update(!isAllHigh, name, cnt_pair);
        }
        for(auto& out:outs) {
            out->check(!isAllHigh, name, cnt_pair);
        }
    }
};
struct rxNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        P_RR("%s -%s-> %s\n", in_name.c_str(), level ? "high":"low", name.c_str());
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
        }
    }
    void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
    }
};

struct bcNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        P_RR("%s -%s-> %s\n", in_name.c_str(), level ? "high":"low", name.c_str());
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
        }
    }
    void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        for(auto& out:outs) {
            out->update(level, name, cnt_pair);
        }
        for(auto& out:outs) {
            out->check(level, name, cnt_pair);
        }
    }
};

std::map<S, std::shared_ptr<Node>> nodes;


auto count1() {
    LL result = 0;
    std::pair<LL,LL> pair{0,0};
    FOR(i, 4LL) {
        nodes["broadcaster"]->update(false, "broadcaster", pair);
        nodes["broadcaster"]->check(false, "broadcaster", pair);
    }
    result = pair.first*pair.second;
    P(pair.first, pair.second, result);
    return result;
}

auto count2() {
    LL result = 0;
    // std::pair<LL,LL> pair{0,0};
    // int cnt = 1;
    // for(;;){
    //     counter++;
    //     if(cnt < counter) {
    //         P(cnt);
    //         cnt*=10;
    //     }
    //     outputH = 0;
    //     outputL = 0;
    //     std::vector<std::pair<S,bool>> mod;
    //     mod.emplace_back("broadcaster", false);
    //     auto local = Push(mod);
    //     pair.first += local.first;
    //     pair.second += local.second;
    //     pair.first += outputH;
    //     pair.second += outputL;
    // }
    // result = pair.first*pair.second;
    return result;
}

int main(int argc, char** argv)
{
    nodes["broadcaster"] = std::make_shared<bcNode>();
    nodes["output"] = std::make_shared<rxNode>();
    nodes["rx"] = std::make_shared<rxNode>();
    for(const auto& l: in){
        auto v = splitStr(l, '>');
        auto name = splitStr(v[0], ' ')[0];
        auto outs = splitStr(v[1], ',');
        char type = name[0];
        if(name == "broadcaster") {
        } else if(type == '%') {
            name.erase(0,1);
            nodes[name] = std::make_shared<ffNode>();
        } else if(type == '&') {
            name.erase(0,1);
            nodes[name] = std::make_shared<cjNode>();
        } else {
            P(type);
            P_LINE;
            exit(1);
        }
    }
    for(auto& node : nodes){
        node.second->name = node.first;
    }
    for(const auto& l: in){
        auto v = splitStr(l, '>');
        auto name = splitStr(v[0], ' ')[0];
        auto shortName = name;
        char type = name[0];
        if(type == '%' || type == '&') {
            shortName.erase(0,1);
        }
        auto outs = splitStr(v[1], ',');
        for(const auto& o : outs){
            auto& node = nodes[o];
            nodes[o]->ins.push_back(nodes[shortName]);
            nodes[o]->levels.push_back(false);
            nodes[shortName]->outs.push_back(nodes[o]);
        }
    }

    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    for(auto& node : nodes){
        for(auto& l : node.second->levels) {
            l = false;
        }
    }
    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
