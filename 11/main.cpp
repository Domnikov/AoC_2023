#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

VECI exp_rows;
VECI exp_cols;
LL exp_value = 1;

bool is_emptyRow(LL l){
    FOR(i, in[l].size()){
        if(in[l][i] != '.') return false;
    }
    return true;
}

bool is_emptyCol(LL c){
    FOR(i, in.size()){
        if(in[i][c] != '.') return false;
    }
    return true;
}

void insertRow(LL l){
    exp_rows.push_back(l);
}

void insertCol(LL c){
    exp_cols.push_back(c);
}

void expand(){
    for(LL i = in.size() - 1; i >= 0; --i){
        if(is_emptyRow(i)){
            insertRow(i);
        }
    }
    for(LL i = in[0].size() - 1; i >= 0; --i){
        if(is_emptyCol(i)){
            insertCol(i);
        }
    }
}

VECPLL GetAllGalaxies(){
    VECPLL g;
    FOR(l, in.size()){
        FOR(c, in[l].size()){
            if(in[l][c] == '#')
            {
                g.emplace_back(l,c);
            }
        }
    }
    return g;
}

auto GetDist(std::pair<LL,LL> g1, std::pair<LL,LL> g2){
    LL dist = labs(g1.first - g2.first) + labs(g1.second-g2.second);
    for(auto l:exp_rows){
        if((g1.first < l && l < g2.first) || (g2.first < l && l < g1.first)) {
            dist += exp_value;
        }
    }
    for(auto c:exp_cols){
        if((g1.second < c && c < g2.second) || (g2.second < c && c < g1.second)) {
            dist += exp_value;
        }
    }
    return dist;
}

auto count() {
    LL result = 0;
    auto g = GetAllGalaxies();

    FOR(i, g.size()){
        for(auto j = i+1; j < g.size(); ++j){
            auto dist = GetDist(g[i], g[j]);
            // P(g[i], g[j], dist);
            result += dist;
        }
    }

    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    expand();
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    exp_value = 999999;
    score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
