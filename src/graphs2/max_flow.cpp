// Edmonds-Karp（Ford-Fulkerson＋BFS 找增廣路徑）：CLRS 圖 24.2 Lucky Puck，最大流 23
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main() {
    const int n = 6, s = 0, t = 5;
    const std::vector<std::string> name = {"s","v1","v2","v3","v4","t"};
    std::vector<std::vector<int>> cap(n, std::vector<int>(n, 0));
    for (auto [u, v, c] : std::vector<std::tuple<int,int,int>>{
             {0,1,16},{0,2,13},{1,3,12},{2,1,4},{2,4,14},
             {3,2,9},{3,5,20},{4,3,7},{4,5,4}})
        cap[u][v] = c;

    int maxFlow = 0;
    while (true) {
        std::vector<int> parent(n, -1);            // BFS 找殘餘網路的增廣路徑
        parent[s] = s;
        std::queue<int> Q; Q.push(s);
        while (!Q.empty() && parent[t] < 0) {
            int u = Q.front(); Q.pop();
            for (int v = 0; v < n; ++v)
                if (parent[v] < 0 && cap[u][v] > 0) {
                    parent[v] = u; Q.push(v);
                }
        }
        if (parent[t] < 0) break;                  // 無增廣路徑 → 已達最大流
        int f = 1e9;                                // 路徑上的殘餘容量瓶頸
        for (int v = t; v != s; v = parent[v]) f = std::min(f, cap[parent[v]][v]);
        std::cout << "增廣路徑：";
        std::vector<int> path;
        for (int v = t; v != s; v = parent[v]) path.push_back(v);
        path.push_back(s);
        for (int i = (int)path.size() - 1; i >= 0; --i)
            std::cout << name[path[i]] << (i ? "→" : "");
        std::cout << "，推 " << f << " 單位\n";
        for (int v = t; v != s; v = parent[v]) {   // 更新殘餘網路（含反向邊）
            cap[parent[v]][v] -= f;
            cap[v][parent[v]] += f;
        }
        maxFlow += f;
    }
    std::cout << "最大流 |f*| = " << maxFlow << "\n";
    return 0;
}
