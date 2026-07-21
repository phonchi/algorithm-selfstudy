// 模擬退火解 TSP：與 ACO 同一組 8 城（CLRS 圖 35.2）——2-opt 鄰居＋幾何降溫
// deterministic LCG（seed=7）供重現
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

unsigned long long seed = 7;
double rnd() {
    seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
    return (seed >> 11) / 9007199254740992.0;
}

int main() {
    std::vector<std::pair<double,double>> P = {
        {1,4},{1,2},{0,1},{3,4},{4,3},{3,2},{5,2},{2,0}};
    const int n = 8;
    auto dist = [&](int i, int j) {
        return std::hypot(P[i].first - P[j].first, P[i].second - P[j].second);
    };
    auto tourCost = [&](const std::vector<int>& t) {
        double c = 0;
        for (int i = 0; i < n; ++i) c += dist(t[i], t[(i + 1) % n]);
        return c;
    };

    std::vector<int> cur(n);
    std::iota(cur.begin(), cur.end(), 0);            // 起始：a b c d e f g h
    double curCost = tourCost(cur), best = curCost;
    double T = 5.0;                                  // 初始溫度
    int accepted_worse = 0;
    for (int it = 0; it < 20000; ++it) {
        int i = 1 + (int)(rnd() * (n - 1));          // 2-opt：反轉區段 [i, j]
        int j = 1 + (int)(rnd() * (n - 1));
        if (i > j) std::swap(i, j);
        if (i == j) continue;
        std::vector<int> nxt = cur;
        std::reverse(nxt.begin() + i, nxt.begin() + j + 1);
        double c = tourCost(nxt);
        double delta = c - curCost;
        if (delta < 0 || rnd() < std::exp(-delta / T)) {   // 變差也可能收（機率 e^{-Δ/T}）
            if (delta > 0) ++accepted_worse;
            cur = nxt; curCost = c;
            best = std::min(best, curCost);
        }
        T *= 0.9995;                                 // 幾何降溫
    }
    std::cout << "SA 最佳成本 = " << best << "（暴力最佳 14.7148）\n";
    std::cout << "接受過 " << accepted_worse << " 次「變差的移動」——高溫期的探索本錢\n";
    return 0;
}
