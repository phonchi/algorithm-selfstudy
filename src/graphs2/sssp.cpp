// Bellman-Ford（CLRS 圖 22.4，含負權）與 Dijkstra（CLRS 圖 22.6）
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int INF = 1e9;
struct Edge { int u, v, w; };

int main() {
    const std::string name = "stxyz";

    // ---- Bellman-Ford：|V|-1 輪全邊鬆弛＋第 |V| 輪驗負環 ----
    std::vector<Edge> E = {{0,1,6},{0,3,7},{1,2,5},{1,3,8},{1,4,-4},
                           {2,1,-2},{3,2,-3},{3,4,9},{4,2,7},{4,0,2}};
    std::vector<int> d(5, INF);
    d[0] = 0;
    for (int round = 1; round <= 4; ++round)          // |V| - 1 = 4 輪
        for (const Edge& e : E)
            if (d[e.u] != INF && d[e.u] + e.w < d[e.v])
                d[e.v] = d[e.u] + e.w;                // RELAX(u, v, w)
    bool ok = true;                                    // 第 |V| 輪：還能鬆 = 負環
    for (const Edge& e : E)
        if (d[e.u] != INF && d[e.u] + e.w < d[e.v]) ok = false;
    std::cout << "Bellman-Ford（源點 s）回傳 " << (ok ? "TRUE" : "FALSE") << "：";
    for (int v = 0; v < 5; ++v) std::cout << name[v] << ":" << d[v] << " ";
    std::cout << "\n";

    // ---- Dijkstra：非負權，priority_queue 貪婪取最近白點 ----
    std::vector<Edge> E2 = {{0,1,10},{0,3,5},{1,2,1},{1,3,2},{2,4,4},
                            {3,1,3},{3,2,9},{3,4,2},{4,0,7},{4,2,6}};
    std::vector<std::vector<std::pair<int,int>>> adj(5);
    for (const Edge& e : E2) adj[e.u].push_back({e.v, e.w});
    std::vector<int> dist(5, INF);
    using PII = std::pair<int,int>;                    // {dist, v}
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> Q;
    dist[0] = 0; Q.push({0, 0});
    while (!Q.empty()) {
        auto [du, u] = Q.top(); Q.pop();
        if (du > dist[u]) continue;                    // 過期項目跳過
        for (auto [v, w] : adj[u])
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; Q.push({dist[v], v});
            }
    }
    std::cout << "Dijkstra（源點 s）：";
    for (int v = 0; v < 5; ++v) std::cout << name[v] << ":" << dist[v] << " ";
    std::cout << "\n";
    return 0;
}
