// 螞蟻演算法（ACO）解 TSP：CLRS 圖 35.2 的 8 城（同 np_approx 頁）——
// 費洛蒙 τ 引導＋能見度 1/d 啟發＋蒸發更新；deterministic LCG 供重現。
#include <cmath>
#include <iostream>
#include <vector>

unsigned long seed = 42;
double rnd() {                                     // LCG：確保結果可重現
    seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
    return (seed >> 11) / 9007199254740992.0;
}

int main() {
    std::vector<std::pair<double,double>> P = {
        {1,4},{1,2},{0,1},{3,4},{4,3},{3,2},{5,2},{2,0}};
    const int n = 8, ants = 8, iters = 40;
    const double alpha = 1, beta = 2, rho = 0.5, Q = 10;
    auto dist = [&](int i, int j) {
        return std::hypot(P[i].first - P[j].first, P[i].second - P[j].second);
    };
    std::vector<std::vector<double>> tau(n, std::vector<double>(n, 1.0));
    std::vector<int> bestTour;
    double bestCost = 1e18;

    for (int it = 1; it <= iters; ++it) {
        std::vector<std::vector<int>> tours;
        for (int a = 0; a < ants; ++a) {
            std::vector<int> tour = {a % n};                   // 每隻螞蟻不同起點
            std::vector<bool> vis(n, false);
            vis[tour[0]] = true;
            for (int step = 1; step < n; ++step) {             // 機率 ∝ τ^α · (1/d)^β
                int u = tour.back();
                std::vector<double> w(n, 0);
                double tot = 0;
                for (int v = 0; v < n; ++v)
                    if (!vis[v]) {
                        w[v] = std::pow(tau[u][v], alpha) * std::pow(1.0 / dist(u, v), beta);
                        tot += w[v];
                    }
                double r = rnd() * tot;
                int pick = -1;
                for (int v = 0; v < n && pick < 0; ++v)
                    if (!vis[v]) { r -= w[v]; if (r <= 0) pick = v; }
                if (pick < 0) for (int v = n - 1; v >= 0; --v) if (!vis[v]) { pick = v; break; }
                tour.push_back(pick); vis[pick] = true;
            }
            tours.push_back(tour);
        }
        for (auto& row : tau) for (double& t : row) t *= (1 - rho);   // 蒸發
        for (const auto& tour : tours) {
            double c = 0;
            for (int i = 0; i < n; ++i) c += dist(tour[i], tour[(i + 1) % n]);
            if (c < bestCost) { bestCost = c; bestTour = tour; }
            for (int i = 0; i < n; ++i) {                      // 沉積：好路多留味
                int u = tour[i], v = tour[(i + 1) % n];
                tau[u][v] += Q / c; tau[v][u] += Q / c;
            }
        }
        if (it == 1 || it == 5 || it == iters)
            std::cout << "iter " << it << "：目前最佳 = " << bestCost << "\n";
    }
    std::cout << "ACO 最佳導覽：";
    for (int v : bestTour) std::cout << "abcdefgh"[v];
    std::cout << "，成本 = " << bestCost << "（暴力最佳 14.7148）\n";
    return 0;
}
