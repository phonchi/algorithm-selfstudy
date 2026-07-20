// Kruskal 與 Prim：CLRS 圖 21.4（a..i，14 條邊），兩者 MST 總權重都是 37
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

std::vector<int> p, rank_;
int findSet(int x) {
    if (p[x] != x) p[x] = findSet(p[x]);
    return p[x];
}
bool unite(int x, int y) {
    int rx = findSet(x), ry = findSet(y);
    if (rx == ry) return false;
    if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
    p[ry] = rx;
    if (rank_[rx] == rank_[ry]) ++rank_[rx];
    return true;
}

struct Edge { int u, v, w; };

int main() {
    const std::string name = "abcdefghi";
    std::vector<Edge> edges = {
        {0,1,4},{0,7,8},{1,7,11},{1,2,8},{2,8,2},{2,5,4},{2,3,7},
        {3,5,14},{3,4,9},{4,5,10},{5,6,2},{6,8,6},{6,7,1},{7,8,7}};

    // ---- Kruskal：邊按權重排序，union-find 擋環 ----
    p.resize(9); std::iota(p.begin(), p.end(), 0);
    rank_.assign(9, 0);
    std::sort(edges.begin(), edges.end(),
              [](const Edge& a, const Edge& b) { return a.w < b.w; });
    int total = 0;
    std::cout << "Kruskal MST：";
    for (const Edge& e : edges)
        if (unite(e.u, e.v)) {
            std::cout << name[e.u] << "-" << name[e.v] << "(" << e.w << ") ";
            total += e.w;
        }
    std::cout << "\n  總權重 = " << total << "\n";

    // ---- Prim：從 a 出發，priority_queue 挑 light edge ----
    std::vector<std::vector<std::pair<int,int>>> adj(9);   // {v, w}
    for (const Edge& e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }
    std::vector<int> key(9, 1e9), parent(9, -1);
    std::vector<bool> inMST(9, false);
    using PII = std::pair<int,int>;                        // {key, v}
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> Q;
    key[0] = 0; Q.push({0, 0});
    total = 0;
    while (!Q.empty()) {
        auto [k, u] = Q.top(); Q.pop();
        if (inMST[u]) continue;
        inMST[u] = true; total += k;
        for (auto [v, w] : adj[u])
            if (!inMST[v] && w < key[v]) {
                key[v] = w; parent[v] = u; Q.push({w, v});
            }
    }
    std::cout << "Prim MST：   ";
    for (int v = 1; v < 9; ++v)
        std::cout << name[parent[v]] << "-" << name[v] << "(" << key[v] << ") ";
    std::cout << "\n  總權重 = " << total << "\n";
    return 0;
}
