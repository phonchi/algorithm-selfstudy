// APPROX-TSP-TOUR：CLRS 圖 35.2 的 8 個點——MST（Prim）＋前序走訪；
// 三角不等式下保證 ≤ 2·OPT。附暴力最佳解對照。
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    const std::string name = "abcdefgh";
    std::vector<std::pair<double,double>> P = {
        {1,4},{1,2},{0,1},{3,4},{4,3},{3,2},{5,2},{2,0}};
    const int n = 8;
    auto dist = [&](int i, int j) {
        return std::hypot(P[i].first - P[j].first, P[i].second - P[j].second);
    };

    // Prim MST（根 = a）
    std::vector<int> parent(n, -1);
    std::vector<double> key(n, 1e18);
    std::vector<bool> in(n, false);
    key[0] = 0;
    for (int it = 0; it < n; ++it) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!in[v] && (u < 0 || key[v] < key[u])) u = v;
        in[u] = true;
        for (int v = 0; v < n; ++v)
            if (!in[v] && dist(u, v) < key[v]) { key[v] = dist(u, v); parent[v] = u; }
    }

    // 前序走訪 MST（子節點按編號序）
    std::vector<std::vector<int>> child(n);
    for (int v = 1; v < n; ++v) child[parent[v]].push_back(v);
    std::vector<int> tour;
    auto preorder = [&](auto&& self, int u) -> void {
        tour.push_back(u);
        for (int c : child[u]) self(self, c);
    };
    preorder(preorder, 0);

    double cost = 0;
    std::cout << "前序導覽：";
    for (int i = 0; i < n; ++i) {
        std::cout << name[tour[i]] << (i + 1 < n ? "→" : "");
        cost += dist(tour[i], tour[(i + 1) % n]);
    }
    std::cout << "→a\n近似導覽成本 = " << cost << "\n";

    // 暴力最佳解（7! = 5040 種）
    std::vector<int> perm(n - 1);
    std::iota(perm.begin(), perm.end(), 1);
    double best = 1e18;
    do {
        double c = dist(0, perm[0]) + dist(perm[n - 2], 0);
        for (int i = 0; i + 1 < n - 1; ++i) c += dist(perm[i], perm[i + 1]);
        best = std::min(best, c);
    } while (std::next_permutation(perm.begin(), perm.end()));
    std::cout << "暴力最佳成本 = " << best << "，比值 = " << cost / best << "（≤ 2 ✓）\n";
    return 0;
}
