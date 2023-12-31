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

S CheckRule(const Work& w, const VECSS& rules){
    for(const auto& rule : rules) {
        if(rule.size() == 1) {
            return rule[0];
        } else {
            S r = rule[0];
            char name = r[0];
            char sign = r[1];
            r.erase(0,2);
            LL num = stoll(r);
            if(w.count(name)){
                if(sign == '>'){
                    if(w.at(name) > num){
                        return rule[1];
                    }
                } else if(sign == '<'){
                    if(w.at(name) < num){
                        return rule[1];
                    }
                }
            }
        }
    }
    P_LINE;
    exit(1);
}

bool Process(const Work& w){
    S cur = "in";
    for(;;){
        const auto& rule = map[cur];
        S res = CheckRule(w, rule);
        if( res == "A" ){
            return true;
        } else if( res == "R" ) {
            return false;
        }
        cur = res;
    }
    P_LINE;
    exit(1);
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

    for(const auto& w:work){
        if(Process(w)){
            for(auto [name, value] : w){
                result += value;
            }
        }
    }


    return result;
}

LL check(S cur, std::map<char, std::pair<LL,LL>> vals){
    LL result = 0;
    if(cur == "A") {
        return (vals['x'].second-vals['x'].first+1) * (vals['m'].second-vals['m'].first+1) * (vals['a'].second-vals['a'].first+1) * (vals['s'].second-vals['s'].first+1);
    } else if(cur == "R") {
        return 0;
    }
    const VECSS rules = map[cur];
    for(const auto& rule:rules) {
        if(rule.size() == 1) {
            return result + check(rule[0], vals);
        } else {
            S r = rule[0];
            char name = r[0];
            char sign = r[1];
            r.erase(0,2);
            LL num = stoll(r);
            if(sign == '>'){
                if(vals[name].second <= num){
                    continue;
                } else if(vals[name].first <= num){
                    auto newVals = vals;
                    newVals[name].first = num+1;
                    result += check(rule[1], newVals);
                    vals[name].second = num;
                } else {
                    return result + check(rule[1], vals);
                }
            } else if(sign == '<'){
                if(vals[name].first >= num){
                    continue;
                } else if(vals[name].second >= num){
                    auto newVals = vals;
                    newVals[name].second = num-1;
                    result += check(rule[1], newVals);
                    vals[name].first = num;
                } else {
                    return result + check(rule[1], vals);
                }
            }
        }
    }
    P_LINE;
    exit(1);
}

auto count2() {
    std::map<char, std::pair<LL,LL>> vals;
    vals['x'] = {1, 4000};
    vals['m'] = {1, 4000};
    vals['a'] = {1, 4000};
    vals['s'] = {1, 4000};
    LL result = check("in", vals);
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
