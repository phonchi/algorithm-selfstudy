// graph_traversal.cpp — CLRS 4e Ch20：BFS 距離、DFS 時間戳、topological sort
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Graph {
    int n;
    std::vector<std::vector<int>> adj;
    explicit Graph(int n) : n(n), adj(n) {}
    void addEdge(int u, int v) { adj[u].push_back(v); }
};

std::vector<int> bfs(const Graph& G, int s) {
    std::vector<int> d(G.n, -1);                 // -1 = WHITE（未發現）
    std::queue<int> Q;
    d[s] = 0; Q.push(s);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : G.adj[u])
            if (d[v] < 0) { d[v] = d[u] + 1; Q.push(v); }   // 第一次發現 = 最短距離
    }
    return d;
}

struct DFS {
    const Graph& G;
    std::vector<int> disc, fin;                  // 發現／完成時間戳
    std::vector<int> order;                      // 完成順序（反轉 = topological sort）
    int time = 0;
    explicit DFS(const Graph& G) : G(G), disc(G.n, 0), fin(G.n, 0) {
        for (int u = 0; u < G.n; ++u)
            if (!disc[u]) visit(u);
    }
    void visit(int u) {
        disc[u] = ++time;                        // 塗灰
        for (int v : G.adj[u])
            if (!disc[v]) visit(v);
        fin[u] = ++time;                         // 塗黑
        order.push_back(u);
    }
};

int main() {
    // CLRS 圖 20.7 的穿衣 DAG：0內褲 1褲子 2皮帶 3襯衫 4領帶 5外套 6襪子 7鞋 8錶
    const std::string name[] = {"內褲","褲子","皮帶","襯衫","領帶","外套","襪子","鞋","錶"};
    Graph G(9);
    int E[][2] = {{0,1},{0,7},{1,2},{1,7},{3,2},{3,4},{4,5},{2,5},{6,7}};
    for (auto [u, v] : E) G.addEdge(u, v);

    DFS d(G);
    std::cout << "topological sort（DFS 完成時間反序）：\n  ";
    for (auto it = d.order.rbegin(); it != d.order.rend(); ++it)
        std::cout << name[*it] << ' ';
    std::cout << '\n';

    // BFS 示範：無向圖 CLRS 圖 20.3（8 頂點 r s t u v w x y = 0..7）
    Graph H(8);
    int E2[][2] = {{0,1},{0,4},{1,5},{5,2},{5,6},{2,3},{2,6},{6,3},{6,7},{3,7}};
    for (auto [u, v] : E2) { H.addEdge(u, v); H.addEdge(v, u); }
    auto dist = bfs(H, 1);                       // 從 s 出發
    const char vn[] = "rstuvwxy";
    std::cout << "BFS 距離（源點 s）：";
    for (int v = 0; v < 8; ++v) std::cout << vn[v] << ":" << dist[v] << ' ';
    std::cout << '\n';
    return 0;
}
