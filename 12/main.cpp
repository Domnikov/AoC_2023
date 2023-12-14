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

// bool IsCorrect(const S& s, const VECI& nums) {
//     auto calced = StrToBrokenVeci(s);
//     // P(s);
//     // P_VEC(calced);
//     // P_VEC(nums);
//     return calced == nums;
// }
//
LL CountUnknowns(const S& s){
    LL counter = 0;
    for(auto c:s){
        if(c == '?') ++counter;
    }
    return counter;
}

// LL permutation = 0;
//
// void resetPerm(){
//     permutation = 0;
// }
//
// bool Next(LL len){
//     return (pow(2, len) > ++permutation);
// }
//
// S GetPermutation(LL len){
//     LL cur = permutation;
//     S result;
//     FOR(i, len){
//         result.push_back((cur%2) ? '#' : '.');
//         cur /= 2;
//     }
//     return result;
// }
//
// S ApplyPerm(S s, LL len){
//     auto perm = GetPermutation(len);
//     for(auto& c:s){
//         if(c == '?'){
//             c = perm.back();
//             perm.pop_back();
//         }
//     }
//     return s;
// }

// bool CheckFromHere(S& s, LL posS, LL num){
bool CheckFromHere(const S& s, LL posS, LL num){
    FOR(i, num){
        if((posS+i) >= s.size()) {
            return false;
        }
        if(s[posS+i] == '.') {
            return false;
        }
        // s[posS+i] = '#';
    }
    if ((posS+num) == (s.size())) {
        return true;
    } else {
        bool result = s[posS+num] != '#';
        // s[posS+num] = '.';
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
    // P(s, places, need);
    return places >= need;
}

LL recursion(const S& s, LL posS, const VECI& nums, LL posN){
    if(!Precheck(s, posS, nums, posN)){
        return 0;
    }
    while(posS < s.size() && s[posS] == '.'){
        ++posS;
    }
    if(s.size() <= posS) {
        if(nums.size() == posN) {
            // P(s);
            return 1;
        }
        return 0;
    } else if(s[posS] == '#'){
        if(posN == nums.size()) {
            return 0;
        }
        // S ss = s;
        LL num = nums[posN];
        // if(!CheckFromHere(ss, posS, num)) {
        if(!CheckFromHere(s, posS, num)) {
            return 0;
        }
        // auto result = recursion(ss, posS+num+1, nums, posN+1, level+1);
        auto result = recursion(s, posS+num+1, nums, posN+1);
        return result;
    } else if(s[posS] == '?') {
        LL total = 0;
        // S ss = s;
        if(posN < nums.size()) {
            LL num = nums[posN];
            // if(CheckFromHere(ss, posS, num)) {
            //     total += recursion(ss, posS+num+1, nums, posN+1, level+1);
            if(CheckFromHere(s, posS, num)) {
                total += recursion(s, posS+num+1, nums, posN+1);
            }
        }
        // S sss = s;
        // sss[posS] = '.';
        // total += recursion(sss, posS+1, nums, posN, level+1);
        total += recursion(s, posS+1, nums, posN);
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
        // P_VEC(nums);
        // P(s);
        local = recursion(s, 0, nums, 0);
        // FOR(i, 0){P_RR("  ");}P_RR("%s:%d\t\t%s\n",__FUNCTION__, __LINE__, s.c_str());
        // resetPerm();
        // do{
        //     auto newS = ApplyPerm(s, unk);
        //     if(IsCorrect(newS, nums)){
        //         local++;
        //     }
        // }while(Next(unk));
        P_RR("%ld\t%lld\n", i, local);
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
return 0;
    UnfoldInput();
    score = count1();
    // for(auto s:in){
    //     score = std::max(score, CountUnknowns(s));
    // }
    P_RR("Part2: %lld\n", score);
    return 0;
}
