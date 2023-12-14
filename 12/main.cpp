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

VECI StrToBrokenVeci(S s){
    VECI result;
    result.push_back(0);
    for(auto c:s){
        if(c == '#'){
            result.back()++;
        }
        else if(result.back()){
            result.push_back(0);
        }
    }
    return result;
}

bool IsCorrect(S s, VECI nums) {
    return StrToBrokenVeci(s) == nums;
}

LL CountUnknowns(S s){
    LL counter = 0;
    for(auto c:s){
        if(c == '?') ++counter;
    }
    return counter;
}

LL permutation = 0;

void resetPerm(){
    permutation = 0;
}

bool Next(LL len){
    return (pow(2, len) > ++permutation);
}

S GetPermutation(LL len){
    LL cur = permutation;
    S result;
    FOR(i, len){
        result.push_back((cur%2) ? '#' : '.');
        cur /= 2;
    }
    return result;
}

S ApplyPerm(S s, LL len){
    auto perm = GetPermutation(len);
    for(auto& c:s){
        if(c == '?'){
            c = perm.back();
            perm.pop_back();
        }
    }
    return s;
}

auto count() {
    LL result = 0;
    FOR(i, in.size()){
        auto numb = GetNumb(i);
        S s = GetLine(i);
        LL unk = CountUnknowns(s);
        P_VEC(numb);
        P(s, unk);
        return 0LL;
        resetPerm();
        do{
            auto newS = ApplyPerm(s, unk);
            if(IsCorrect(newS, numb)){
                result++;
            }
        }while(Next(unk));
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
