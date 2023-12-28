#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto input = getInput();

LL R = input.size();
LL C = input[0].size();

class Elf {
  public:
    Elf(LL r, LL c) {
        static LL counter = 0;
        row=r;
        col=c;
    }
    LL id;
    LL row;
    LL col;
};

std::ostream& operator<<(std::ostream& os, const Elf& me) {
    os<<"Elf("<<me.row<<","<<me.col<<")";
    return os;
}

bool operator<(const Elf& lhs, const Elf& rhs) {
    LL s1 = lhs.row*1000+lhs.col;
    LL s2 = rhs.row*1000+rhs.col;
    return s1 < s2;
}

bool operator==(const Elf& lhs, const Elf& rhs) {
    LL s1 = lhs.row*1000+lhs.col;
    LL s2 = rhs.row*1000+rhs.col;
    return s1 == s2;
}

Elf operator+(const Elf& lhs, const Elf& rhs) {
    return Elf{lhs.row+rhs.row, lhs.col+rhs.col};
}

Elf GetFirst(){
    FOR(row, input.size()){
        FOR(col, input[row].size()){
            if(input[row][col] == 'S'){
                return Elf{(LL)row, (LL)col};
            }
        }
    }
    exit(1);
}

void step(std::set<Elf>& elfs){
    std::set<Elf> copy;
    for(auto& org:elfs){
        if((org.row - 1) >= 0                       && input[org.row - 1][org.col    ] != '#') {copy.emplace(org.row - 1, org.col    );}
        if((org.row + 1) <  R                       && input[org.row + 1][org.col    ] != '#') {copy.emplace(org.row + 1, org.col    );}
        if(                      (org.col - 1) >= 0 && input[org.row    ][org.col - 1] != '#') {copy.emplace(org.row    , org.col - 1);}
        if(                      (org.col + 1) <  C && input[org.row    ][org.col + 1] != '#') {copy.emplace(org.row    , org.col + 1);}
    }
    elfs.swap(copy);
}

auto count1() {
    LL result = 0;
    std::set<Elf> elfs{GetFirst()};

    LL N = 64;
    LL counter = 1;
    FOR(i, N){
        step(elfs);
        if(i > counter){
            counter *= 10;
        }
    }
    auto in2 = input;
    result = elfs.size();
    return result;
}

auto count2() {
    LL result = 0;
    const int N = 26501365;
    auto first = GetFirst();
    first.row += R;
    first.col += C;

    VECII dist(3*R, VECI(3*C, 0));

    VECS in3 = Expand(input, 3);
    std::vector<std::vector<bool>> vis(3*R, std::vector<bool>(3*C));
    std::queue<Elf> q;
    q.push(first);
    vis[first.row][first.col] = true;

    Elf Mod[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while(!q.empty()) {
        Elf u = q.front();
        q.pop();
        for(int j = 0; j < 4; j++) {
            auto d = Mod[j];
            auto v = u + d;
            if((0 <= v.row && v.row < 3*R && 0 <= v.col && v.col < 3*C) && in3[v.row][v.col] != '#' && !vis[v.row][v.col]) {
                vis[v.row][v.col] = true;
                dist[v.row][v.col] = dist[u.row][u.col] + 1;
                q.push(v);
            }
        }
    }

    VECI dp(N + 1000);
    for(LL i = N; i >= 0; i--) {
        dp[i] = (i % 2 == N % 2) + 2 * dp[i+R] - dp[i+2*R];
    }


    FOR(i, 3*R){
        FOR(j, 3*C){
            if(!vis[i][j]) continue;
            LL drow = i - first.row;
            LL dcol = j - first.col;
            if(-R <= drow && drow < R && -C <= dcol && dcol < C) {
                result += dp[dist[i][j]];
            }
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
