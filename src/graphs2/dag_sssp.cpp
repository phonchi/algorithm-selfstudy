// DAG 最短路徑（CLRS §22.2）：拓撲排序後按序單趟鬆弛——負權 OK、Θ(V+E)
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const long long INF = 1e18;
std::vector<std::vector<std::pair<int,int>>> adj;   // {v, w}
std::vector<int> order;
std::vector<bool> visited;

void visit(int u) {
    visited[u] = true;
    for (auto [v, w] : adj[u])
        if (!visited[v]) visit(v);
    order.push_back(u);                     // 完成時 push → 反轉即拓撲序
}

int main() {
    const std::string name = "rstxyz";      // CLRS 圖 22.5
    adj = {{{1,5},{2,3}}, {{2,2},{3,6}}, {{3,7},{4,4},{5,2}},
           {{4,-1},{5,1}}, {{5,-2}}, {}};
    int n = adj.size();
    visited.assign(n, false);
    for (int u = 0; u < n; ++u)
        if (!visited[u]) visit(u);
    std::reverse(order.begin(), order.end());

    std::vector<long long> d(n, INF);
    d[1] = 0;                               // 源點 s
    for (int u : order) {                   // 按拓撲序，每邊恰鬆弛一次
        if (d[u] == INF) continue;
        for (auto [v, w] : adj[u])
            if (d[u] + w < d[v]) d[v] = d[u] + w;
    }
    std::cout << "DAG-SHORTEST-PATHS（源點 s）：";
    for (int v = 0; v < n; ++v)
        std::cout << name[v] << ":" << (d[v] == INF ? std::string("∞") : std::to_string(d[v])) << " ";
    std::cout << "\n";
    return 0;
}
