#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

LL R = in.size();
LL C = in[0].size();

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

Elf GetFirst(){
    FOR(row, in.size()){
        FOR(col, in[row].size()){
            if(in[row][col] == 'S'){
                return Elf{(LL)row, (LL)col};
            }
        }
    }
    exit(1);
}

VECS GetField(std::set<Elf> elfs) {
    auto in2 = in;
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
        if((org.row - 1) >= 0                       && in[org.row - 1][org.col    ] != '#') {copy.emplace(org.row - 1, org.col    );}
        if((org.row + 1) <  R                       && in[org.row + 1][org.col    ] != '#') {copy.emplace(org.row + 1, org.col    );}
        if(                      (org.col - 1) >= 0 && in[org.row    ][org.col - 1] != '#') {copy.emplace(org.row    , org.col - 1);}
        if(                      (org.col + 1) <  C && in[org.row    ][org.col + 1] != '#') {copy.emplace(org.row    , org.col + 1);}
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
    auto in2 = in;
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
            {LL nr = (org.row - 1); LL nc = (org.col); if(nr >= 0) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[0].row == -1){result.next[0] = i;result.dir[0].row =R-1; result.dir[0].col = nc;}}}
            {LL nr = (org.row + 1); LL nc = (org.col); if(nr <  R) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[1].row == -1){result.next[1] = i;result.dir[1].row =  0; result.dir[1].col = nc;}}}
            {LL nc = (org.col - 1); LL nr = (org.row); if(nc >= 0) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[2].row == -1){result.next[2] = i;result.dir[2].row = nr; result.dir[2].col =C-1;}}}
            {LL nc = (org.col + 1); LL nr = (org.row); if(nc <  C) { if(in[nr][nc] != '#') {cur.emplace(nr,nc);}}else{if(result.dir[3].row == -1){result.next[3] = i;result.dir[3].row = nr; result.dir[3].col =  0;}}}
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

    auto first = GetFirst();

    std::map<Elf, Cache> cache;

    cache[first] = Generate(first);

    LL N = 5000;
    // LL N = 26501365;
    std::queue<std::tuple<Elf, LL, LL, LL>> q;
    q.emplace(first, N, 0, 0);
    std::set<std::pair<LL,LL>> used;
    used.emplace(0,0);

    while(!q.empty()){
        auto [elf, stp, X, Y] = q.front();
        if(cache.count(elf) == 0) {
            cache[elf] = Generate(elf);
        }
        auto& local = cache[elf];
        // P(stp, X, Y, GetElfs(stp, local));
        q.pop();
        result += GetElfs(stp, local);
        FOR(i, 4) {
            LL x = X, y = Y;
            switch(i) {
                case 0: ++y;break;
                case 1: --y;break;
                case 2: --x;break;
                case 3: ++x;break;
            }
            if(used.count(std::make_pair(x, y)) == 0) {
                used.emplace(x,y);
                if(local.dir[i] == Elf{-1,-1}) continue;
                if(stp > local.next[i]) {
                    q.emplace(local.dir[i], stp - local.next[i] - 1, x, y);
                }
            } else {
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
