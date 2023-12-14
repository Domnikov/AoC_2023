#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

std::pair<LL,LL> FindReflH(const VECS& pattern) {
    for(size_t i = 1; i < pattern.size(); ++i) {
        LL left = i-1;
        LL right = i;
        while(pattern[left] == pattern[right]) {
            if( (--left < 0) || (++right == pattern.size())){
                return {i-1,i};
            }
        }
    }
    return{0LL,0LL};
}

bool compV(const VECS& pattern, LL left, LL right) {
    FOR(j, pattern.size()){
        if(pattern[j][left] != pattern[j][right]) {
            return false;
        }
    }
    return true;
}

std::pair<LL,LL> FindReflV(const VECS& pattern) {
    for(size_t i = 1; i < pattern[0].size(); ++i) {
        LL left = i-1;
        LL right = i;
        while(compV(pattern, left, right)) {
            if( (--left < 0) || (++right == pattern[0].size())){
                return {i-1,i};
            }
        }
    }
    return{0LL,0LL};
}

auto count() {
    LL result = 0;

    VECS pattern;
    for(const auto& s:in){
        if(!s.empty()){
            pattern.push_back(s);
        } else {
            auto localH = FindReflH(pattern);
            auto localV = FindReflV(pattern);
            P(localH, localV);
            pattern.clear();
            result += 100*localH.second;
            result += localV.second;
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
