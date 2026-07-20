// 生日悖論（CLRS §5.4.1）：理論值 vs 蒙地卡羅模擬（mt19937 seed=42）
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> day(0, 364);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << " n   理論 P(撞期)   模擬(10萬次)   期望撞期配對數 C(n,2)/365\n";
    for (int n : {10, 23, 41, 60}) {
        double pNo = 1.0;                                  // 全不同天的機率
        for (int i = 0; i < n; ++i) pNo *= (365.0 - i) / 365.0;
        const int T = 100000;
        int hit = 0;
        for (int t = 0; t < T; ++t) {
            std::vector<bool> seen(365, false);
            bool coll = false;
            for (int i = 0; i < n && !coll; ++i) {
                int d = day(rng);
                if (seen[d]) coll = true;
                seen[d] = true;
            }
            hit += coll;
        }
        std::cout << std::setw(2) << n << "      " << 1 - pNo
                  << "          " << double(hit) / T
                  << "          " << n * (n - 1) / 2.0 / 365 << "\n";
    }
    return 0;
}
