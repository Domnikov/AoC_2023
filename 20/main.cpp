#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();
LL counter = 1;
std::map<S, LL> allCj;

struct Node{
    virtual void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) = 0;
    virtual void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) = 0;

    std::vector<LL> levels;
    std::map<S, LL> cnt;
    bool isCj = false;

    S name;

    std::vector<std::shared_ptr<Node>> ins;
    std::vector<std::shared_ptr<Node>> outs;
};

struct ffNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
        }
        if(!level) {
            levels[0] = !levels[0];
        }
        // P_RR("%s -%s-> %s[%s]\n", in_name.c_str(), level ? "high":"low", name.c_str(), levels[0] ? "high":"low");
    }
    void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        if(!level) {
            for(auto& out:outs) {
                out->update(levels[0], name, cnt_pair);
            }
            for(auto& out:outs) {
                out->check(levels[0], name, cnt_pair);
            }
        }
    }
};
std::map<std::pair<S, S>, LL> per;
struct cjNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
        }
        FOR(i, levels.size()){
            if(ins[i]->name == in_name) {
                levels[i] = level;
                //P_RR("%s -%s-> %s[%s]\n", in_name.c_str(), level ? "high":"low", name.c_str(), levels[i] ? "high":"low");
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
        if(/*!isAllHigh && counter > 1 &&*/ (name == "vg" || name == "kp" || name == "gc" || name == "tx" )) {
                if(allCj.count (name ) == 0){
                    P(counter, in_name, name, levels.size());
                    allCj[name] = counter;
                    // if( allCj.size() == 4) {exit(0);}
                }
            // }
            // auto key = std::make_pair(name, in_name);
            // if(per.count(key) == 0){
            //     P(counter, in_name, name);
            // }
            // per[key] = (counter);
            // cnt[in_name] = counter;
            // isCj = true;
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
        // P_RR("%s -%s-> %s\n", in_name.c_str(), level ? "high":"low", name.c_str());
        if(level) {
            cnt_pair.first++;
        } else {
            cnt_pair.second++;
            P(counter);
            exit(0);
        }
    }
    void check(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
    }
};

struct bcNode : Node{
    void update(bool level, const S& in_name, std::pair<LL,LL>& cnt_pair) override {
        // P_RR("%s -%s-> %s\n", in_name.c_str(), level ? "high":"low", name.c_str());
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
    FOR(i, 1000LL) {
        nodes["broadcaster"]->update(false, "broadcaster", pair);
        nodes["broadcaster"]->check(false, "broadcaster", pair);

        // for(auto& [name,node]:nodes){
        //     if(node->isCj){
        //         if(node->cnt.size() == node->outs.size()){
        //         }
        //     }
        // }
    }
    result = pair.first*pair.second;
    P(pair.first, pair.second, result);
    return result;
}

auto count2() {
    LL result = 0;
    std::pair<LL,LL> pair{0,0};
    LL cnt = 1;
    per.clear();
    for(;;) {
        nodes["broadcaster"]->update(false, "broadcaster", pair);
        nodes["broadcaster"]->check(false, "broadcaster", pair);
        counter++;
        if(cnt<counter){
            P(cnt);
            cnt*=10;
        }
    }
    result = pair.first*pair.second;
    P(pair.first, pair.second, result);
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
    // score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    for(auto& node : nodes){
        P(node.second->name, node.second->levels);
        for(auto& l : node.second->levels) {
            l = false;
        }
    }
    score = count2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
