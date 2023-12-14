#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

S GetLine(LL i){
    return splitStr(in[i], ' ')[0];
}

VECI GetNumb(LL i){
    return vecsToVeci(splitStr(splitStr(in[i], ' ')[1], ','));
}

VECI StrToBrokenVeci(const S& s){
    VECI result;
    result.reserve(20);
    result.push_back(0);
    for(auto c:s){
        if(c == '#'){
            result.back()++;
        }
        else if(result.back()){
            result.push_back(0);
        }
    }
    if(!result.back()){
        result.pop_back();
    }
    return result;
}

LL CountUnknowns(const S& s){
    LL counter = 0;
    for(auto c:s){
        if(c == '?') ++counter;
    }
    return counter;
}


bool CheckFromHere(const S& s, LL posS, LL num){
    FOR(i, num){
        if((posS+i) >= s.size()) {
            return false;
        }
        if(s[posS+i] == '.') {
            return false;
        }
    }
    if ((posS+num) == (s.size())) {
        return true;
    } else {
        bool result = s[posS+num] != '#';
        return result;
    }
}

bool Precheck(const S& s, LL posS, const VECI& nums, LL posN){
    LL places = 0;
    LL need = 0;

    for(size_t i = posS; i < s.size(); i++){
        if(s[i] != '.'){
            ++places;
        }
    }
    for(size_t i = posN; i < nums.size(); i++){
        need += nums[i];
    }
    return places >= need;
}

LL recursion(const S& s, LL posS, const VECI& nums, LL posN, std::map<std::pair<LL,LL>, LL>& cache){
    if(auto it = cache.find({posS, posN}); it != cache.end()) {
        return it->second;
    }
    if(posS*2 > s.size() && !Precheck(s, posS, nums, posN)){
        cache[{posS, posN}] = 0;
        return 0;
    }
    while(posS < s.size() && s[posS] == '.'){
        ++posS;
    }
    if(s.size() <= posS) {
        if(nums.size() == posN) {
            return 1;
        }
        return 0;
    } else if(s[posS] == '#'){
        if(posN == nums.size()) {
            cache[{posS, posN}] = 0;
            return 0;
        }
        LL num = nums[posN];
        if(!CheckFromHere(s, posS, num)) {
            cache[{posS, posN}] = 0;
            return 0;
        }
        auto result = recursion(s, posS+num+1, nums, posN+1, cache);
        return result;
    } else if(s[posS] == '?') {
        LL total = 0;
        if(posN < nums.size()) {
            LL num = nums[posN];
            if(CheckFromHere(s, posS, num)) {
                total += recursion(s, posS+num+1, nums, posN+1, cache);
            }
        }
        total += recursion(s, posS+1, nums, posN, cache);
        cache[{posS, posN}] = total;
        return total;
    } else {
        P(s, posS, s[posS], nums.size(), posN);
        exit(1);
    }
}

auto count1() {
    LL result = 0;
    FOR(i, in.size()){
        auto nums = GetNumb(i);
        const S& s = GetLine(i);
        LL unk = CountUnknowns(s);
        LL local = 0;
        std::map<std::pair<LL,LL>, LL> cache;
        local = recursion(s, 0, nums, 0, cache);
        result += local;
    }
    return result;
}

void UnfoldInput() {
    FOR(i, in.size()){
        auto s = GetLine(i);
        auto nums = splitStr(in[i], ' ')[1];
        S ss = s,nn = nums;
        FOR(i,4){
            ss += '?' + s;
            nn += ',' + nums;
        }
        in[i] = ss + ' ' + nn;
    }
}

LL count2(){
    P_VEC(in);
    return 0;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    UnfoldInput();
    score = count1();
    P_RR("Part2: %lld\n", score);
    return 0;
}
