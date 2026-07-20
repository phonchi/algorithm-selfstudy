// disjoint_set.cpp — CLRS 4e Ch19：union by rank ＋ path compression
#include <iostream>
#include <numeric>
#include <vector>

struct DisjointSet {
    std::vector<int> p, rank_;
    explicit DisjointSet(int n) : p(n), rank_(n, 0) {
        std::iota(p.begin(), p.end(), 0);        // MAKE-SET：自己當代表
    }
    int findSet(int x) {
        if (p[x] != x) p[x] = findSet(p[x]);     // path compression：沿途全指向根
        return p[x];
    }
    void unite(int x, int y) {                   // union by rank：矮樹掛高樹
        int rx = findSet(x), ry = findSet(y);
        if (rx == ry) return;
        if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
        p[ry] = rx;
        if (rank_[rx] == rank_[ry]) ++rank_[rx];
    }
};

int main() {
    // CLRS 圖 19.1 的連通元件例：10 個頂點 a..j（0..9）
    DisjointSet D(10);
    int edges[][2] = {{1,2},{0,2},{0,1},{3,2},{4,5},{6,7},{8,9}};   // b-c a-c a-b d-c e-f g-h i-j
    for (auto [u, v] : edges) D.unite(u, v);
    const char* name = "abcdefghij";
    std::cout << "SAME-COMPONENT(a, d) = " << (D.findSet(0) == D.findSet(3)) << '\n';
    std::cout << "SAME-COMPONENT(e, g) = " << (D.findSet(4) == D.findSet(6)) << '\n';
    std::cout << "各頂點代表：";
    for (int v = 0; v < 10; ++v) std::cout << name[v] << "→" << name[D.findSet(v)] << ' ';
    std::cout << '\n';
    return 0;
}
