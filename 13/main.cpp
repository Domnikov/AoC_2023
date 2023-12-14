#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

std::pair<LL,LL> FindReflH(const VECS& pattern, std::pair<LL,LL> origin = {0LL, 0LL}) {
    for(size_t i = 1; i < pattern.size(); ++i) {
        LL left = i-1;
        LL right = i;
        if(origin == std::make_pair(left, right)) {
            continue;
        }
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

std::pair<LL,LL> FindReflV(const VECS& pattern, std::pair<LL,LL> origin = {0LL, 0LL}) {
    for(size_t i = 1; i < pattern[0].size(); ++i) {
        LL left = i-1;
        LL right = i;
        if(origin == std::make_pair(left, right)) {
            continue;
        }
        while(compV(pattern, left, right)) {
            if( (--left < 0) || (++right == pattern[0].size())){
                return {i-1,i};
            }
        }
    }
    return{0LL,0LL};
}

auto count1() {
    LL result = 0;

    VECS pattern;
    for(const auto& s:in){
        if(!s.empty()){
            pattern.push_back(s);
        } else {
            auto localH = FindReflH(pattern);
            auto localV = FindReflV(pattern);
            pattern.clear();
            result += 100*localH.second;
            result += localV.second;
        }
    }

    return result;
}

LL CheckAll(VECS pattern){
    auto null = std::make_pair(0LL,0LL);
    auto originH = FindReflH(pattern);
    auto originV = FindReflV(pattern);
    FOR(row, pattern.size()){
        FOR(col, pattern[row].size()){
            pattern[row][col] = pattern[row][col] == '#' ? '.' : '#';
            auto localH = FindReflH(pattern, originH);
            auto localV = FindReflV(pattern, originV);
            if(localH != null || localV != null) {
                LL result = 100*localH.second;
                result += localV.second;
                return result;
            }
            pattern[row][col] = pattern[row][col] == '#' ? '.' : '#';
        }
    }
    P_LINE;
    exit(1);
}

auto count2() {
    LL result = 0;

    VECS pattern;
    for(const auto& s:in){
        if(!s.empty()){
            pattern.push_back(s);
        } else {
            auto local = CheckAll(pattern);
            result += local;
            pattern.clear();
        }
    }

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
