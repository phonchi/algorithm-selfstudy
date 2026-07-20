// scc.cpp — CLRS 4e §20.5：兩趟 DFS 求強連通元件（G 一趟、Gᵀ 按完成時間反序一趟）
#include <iostream>
#include <vector>

int n;
std::vector<std::vector<int>> adj, radj;
std::vector<int> visited, order, comp;

void dfs1(int u) {
    visited[u] = 1;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    order.push_back(u);                          // 完成時間遞增
}
void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : radj[u]) if (comp[v] < 0) dfs2(v, c);
}

int main() {
    // CLRS 圖 20.9：a..h = 0..7
    n = 8;
    adj.assign(n, {}); radj.assign(n, {});
    int E[][2] = {{0,1},{1,2},{1,4},{1,5},{2,3},{2,6},{3,2},{3,7},
                  {4,0},{4,5},{5,6},{6,5},{6,7},{7,7}};
    for (auto [u, v] : E) { adj[u].push_back(v); radj[v].push_back(u); }

    visited.assign(n, 0);
    for (int u = 0; u < n; ++u) if (!visited[u]) dfs1(u);

    comp.assign(n, -1);
    int c = 0;
    for (auto it = order.rbegin(); it != order.rend(); ++it)   // 完成時間遞減
        if (comp[*it] < 0) dfs2(*it, c++);

    std::cout << "共 " << c << " 個 SCC：\n";
    for (int k = 0; k < c; ++k) {
        std::cout << "  { ";
        for (int v = 0; v < n; ++v)
            if (comp[v] == k) std::cout << char('a' + v) << ' ';
        std::cout << "}\n";
    }
    return 0;
}
