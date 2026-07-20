// k-means（CLRS 4e §33.1 Lloyd's algorithm）：8 個 2D 點分 2 群，初始中心取前兩點
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<double,double>> P = {
        {1,1},{1.5,2},{2,1.5},{1,2},{6,5},{6.5,6},{7,5.5},{6,6}};
    const int n = 8, k = 2;
    std::vector<std::pair<double,double>> c = {P[0], P[1]};   // 初始中心
    std::vector<int> assign(n, -1);

    for (int iter = 1; iter <= 10; ++iter) {
        bool changed = false;
        for (int i = 0; i < n; ++i) {                          // 指派步：找最近中心
            int best = 0;
            double bd = 1e18;
            for (int j = 0; j < k; ++j) {
                double d = std::hypot(P[i].first - c[j].first, P[i].second - c[j].second);
                if (d < bd) { bd = d; best = j; }
            }
            if (assign[i] != best) { assign[i] = best; changed = true; }
        }
        for (int j = 0; j < k; ++j) {                          // 更新步：中心 = 群平均
            double sx = 0, sy = 0; int cnt = 0;
            for (int i = 0; i < n; ++i)
                if (assign[i] == j) { sx += P[i].first; sy += P[i].second; ++cnt; }
            if (cnt) c[j] = {sx / cnt, sy / cnt};
        }
        std::cout << "iter " << iter << "：分群 ";
        for (int i = 0; i < n; ++i) std::cout << assign[i];
        std::cout << "，中心 (" << c[0].first << ", " << c[0].second << ") ("
                  << c[1].first << ", " << c[1].second << ")\n";
        if (!changed) { std::cout << "指派不再變動，收斂。\n"; break; }
    }
    return 0;
}
