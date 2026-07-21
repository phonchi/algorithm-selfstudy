// Johnson APSP（CLRS §23.3）：超級源點 Bellman-Ford 求 h → 重加權 → V 次 Dijkstra
#include <iostream>
#include <queue>
#include <vector>

const long long INF = 1e18;
struct Edge { int u, v; long long w; };

int main() {
    const int n = 5;                                 // CLRS 圖 23.1
    std::vector<Edge> E = {{0,1,3},{0,2,8},{0,4,-4},{1,3,1},{1,4,7},
                           {2,1,4},{3,0,2},{3,2,-5},{4,3,6}};

    // ① 超級源點 q（編號 n）連到所有頂點，Bellman-Ford 求 h
    std::vector<Edge> Eq = E;
    for (int v = 0; v < n; ++v) Eq.push_back({n, v, 0});
    std::vector<long long> h(n + 1, 0);              // d(q,·) 初值 0 起跑
    for (int i = 0; i < n; ++i)
        for (const Edge& e : Eq)
            if (h[e.u] + e.w < h[e.v]) h[e.v] = h[e.u] + e.w;
    std::cout << "h = ";
    for (int v = 0; v < n; ++v) std::cout << h[v] << " ";
    std::cout << "\n";

    // ② 重加權 w' = w + h(u) − h(v) ≥ 0
    std::vector<std::vector<std::pair<int,long long>>> adj(n);
    for (const Edge& e : E) adj[e.u].push_back({e.v, e.w + h[e.u] - h[e.v]});

    // ③ 每個源點 Dijkstra，再還原距離
    std::cout << "D（與 Floyd-Warshall 相同）：\n";
    for (int s = 0; s < n; ++s) {
        std::vector<long long> dist(n, INF);
        using P = std::pair<long long,int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        dist[s] = 0; pq.push({0, s});
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du > dist[u]) continue;
            for (auto [v, w] : adj[u])
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
        }
        std::cout << "  ";
        for (int v = 0; v < n; ++v)
            std::cout << dist[v] + h[v] - h[s] << " ";   // 還原原權重距離
        std::cout << "\n";
    }
    return 0;
}
