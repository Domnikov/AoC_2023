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

VECS GetField(std::set<Elf> elfs) {
    auto in2 = input;
    for(const auto& e:elfs){
        in2[e.row][e.col] = 'O';
    }
    return in2;
}

std::ostream& operator<<(std::ostream& os, const std::set<Elf>& elfs) {
    P_VECV(GetField(elfs));
    return os;
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
        // P(i, elfs);
        if(i > counter){
            // P(counter);
            counter *= 10;
        }
    }
    auto in2 = input;
    result = elfs.size();
    // P(elfs);
    return result;
}

struct Cache{
    VECI next{-1,-1,-1,-1};
    std::vector<Elf> dir{4, {-1, -1}};
    VECI data;
};

Cache Generate(Elf init){
    Cache result;
    std::set<Elf> cur{init};
    std::set<Elf> prev;
    std::set<Elf> preprev;
    FOR(i, 10000){
        result.data.push_back(cur.size());
        std::exchange(preprev, std::exchange(prev, std::exchange(cur, {})));
        for(auto& org:prev){
            {LL nr = (org.row - 1); LL nc = (org.col); if(nr >= 0) { if(input[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[0].row == -1){result.next[0] = i;result.dir[0].row =R-1; result.dir[0].col = nc;}}}
            {LL nr = (org.row + 1); LL nc = (org.col); if(nr <  R) { if(input[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[1].row == -1){result.next[1] = i;result.dir[1].row =  0; result.dir[1].col = nc;}}}
            {LL nc = (org.col - 1); LL nr = (org.row); if(nc >= 0) { if(input[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[2].row == -1){result.next[2] = i;result.dir[2].row = nr; result.dir[2].col =C-1;}}}
            {LL nc = (org.col + 1); LL nr = (org.row); if(nc <  C) { if(input[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[3].row == -1){result.next[3] = i;result.dir[3].row = nr; result.dir[3].col =  0;}}}
        }
        // P(i, cur);
        if(cur == preprev) {
            // P(init, result.next);
            // P(cur);
            // P(prev);
            return result;
        }
    }
    exit(1);
}

bool less(LL N, LL NR, LL NC, LL row, LL col) {
    LL r = llabs(NR - row);
    LL c = llabs(NC - col);
    return N*N > ((r*r) + (c*c));
}

LL GetElfs(LL step, const Cache& cache) {
    if(step < cache.data.size()){
        return cache.data[step];
    }
    return cache.data[(step-cache.data.size())% 2 ? (cache.data.size() - 1) : (cache.data.size() - 2)];
}

auto count2() {
    LL result = 0;
    const int N = 26501365;
    auto start = GetFirst();

    start.row += R;
    start.col += C;
    VECII dist(3*R, VECI(3*C, 0));

    VECS in3 = Expand(input, 3);
    std::vector<std::vector<bool>> vis(3*R, std::vector<bool>(3*C));
    std::queue<Elf> q;
    q.push(start);
    vis[start.row][start.col] = true;

    auto inside = [&](Elf p) {
        return 0 <= p.row && p.row < 3*R && 0 <= p.col && p.col < 3*C;
    };

    Elf Mod[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while(!q.empty()) {
        Elf u = q.front();
        q.pop();
        for(int j = 0; j < 4; j++) {
            auto d = Mod[j];
            auto v = u + d;
            if(inside(v) && in3[v.row][v.col] != '#' && !vis[v.row][v.col]) {
                vis[v.row][v.col] = true;
                dist[v.row][v.col] = dist[u.row][u.col] + 1;
                q.push(v);
            }
        }
    }

    VECI dp(N + 1000);
    for(int i = N; i >= 0; i--) {
        dp[i] = (i % 2 == N % 2) + 2 * dp[i+R] - dp[i+2*R];
    }


    FOR(i, 3*R){
        FOR(j, 3*C){
            if(!vis[i][j]) continue;
            int dx = i - start.row;
            int dy = j - start.col;
            if(-R <= dx && dx < R && -C <= dy && dy < C) {
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
