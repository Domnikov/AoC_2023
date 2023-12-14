#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL FindRefl(const VECS& pattern){
    for(size_t i = 1; i < pattern.size(); ++i){
        if(pattern[i-1] == pattern[i]) {
            return i-1;
        }
    }
    for(size_t i = 1; i < pattern[0].size(); ++i){
        bool find = true;
        FOR(j, pattern.size()){
            if(pattern[j][i-1] != pattern[j][i]){
                find = false;
                break;
            }
        }
        if(find){
            return i-1;
        }
    }
    P_LINE;
    exit(1);
}

auto count() {
    LL result = 0;

    VECS pattern;
    for(const auto& s:in){
        if(!s.empty()){
            pattern.push_back(s);
        } else {
            auto local = FindRefl(pattern);
            P(local);
            pattern.clear();
            result += local;
        }
    }

    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
