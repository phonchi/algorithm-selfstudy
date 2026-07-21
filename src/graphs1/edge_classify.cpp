// DFS 邊分類（CLRS §20.3）：探索 (u,v) 時看 v 的顏色——
// 白 = tree、灰 = back（有環！）、黑且 d[u] < d[v] = forward、黑且 d[u] > d[v] = cross
#include <iostream>
#include <string>
#include <vector>

int timer = 0;
std::vector<int> d, f;                       // 發現／完成時間戳
std::vector<int> color;                      // 0 白 1 灰 2 黑
std::vector<std::vector<int>> adj;
std::string names = "abcdefgh";

void visit(int u) {
    color[u] = 1; d[u] = ++timer;
    for (int v : adj[u]) {
        std::string type;
        if (color[v] == 0) type = "tree";
        else if (color[v] == 1) type = "back";
        else type = (d[u] < d[v]) ? "forward" : "cross";
        std::cout << "  " << names[u] << "->" << names[v] << " : " << type << "\n";
        if (color[v] == 0) visit(v);
    }
    color[u] = 2; f[u] = ++timer;
}

int main() {
    // CLRS 圖 20.9 的有向圖（SCC 同款例子）
    adj = {{1}, {2, 4, 5}, {3, 6}, {2, 7}, {0, 5}, {6}, {5, 7}, {7}};
    int n = adj.size();
    d.assign(n, 0); f.assign(n, 0); color.assign(n, 0);
    std::cout << "邊分類（依 DFS 探索順序）：\n";
    for (int u = 0; u < n; ++u)
        if (color[u] == 0) visit(u);
    std::cout << "時間戳 [d, f]：";
    for (int u = 0; u < n; ++u)
        std::cout << names[u] << "[" << d[u] << "," << f[u] << "] ";
    std::cout << "\n";
    return 0;
}
