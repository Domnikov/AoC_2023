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

bool IsCorrect(const S& s, const VECI& nums) {
    auto calced = StrToBrokenVeci(s);
    // P(s);
    // P_VEC(calced);
    // P_VEC(nums);
    return calced == nums;
}

LL CountUnknowns(const S& s){
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

auto count1() {
    LL result = 0;
    FOR(i, in.size()){
        auto numb = GetNumb(i);
        const S& s = GetLine(i);
        LL unk = CountUnknowns(s);
        resetPerm();
        // P_VEC(numb);
        do{
            auto newS = ApplyPerm(s, unk);
            // P(s, newS, IsCorrect(newS, numb));
            if(IsCorrect(newS, numb)){
                result++;
            }
        }while(Next(unk));

        P_RR("%ld%%\n",100*i/in.size());
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
    // score = count1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    UnfoldInput();
    score = count1();
    P_RR("Part2: %lld\n", score);
    return 0;
}
