// hiring.cpp — CLRS 4e Ch5 hiring problem 模擬：
// 隨機排列下期望雇用次數 = H_n ≈ ln n + 0.577
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

int hireCount(std::vector<int>& rank, std::mt19937& rng) {
    std::shuffle(rank.begin(), rank.end(), rng);   // RANDOMIZED-HIRE-ASSISTANT 的第一步
    int best = -1, hires = 0;
    for (int r : rank)
        if (r > best) { best = r; ++hires; }       // 比目前最佳者好 → 雇用
    return hires;
}

int main() {
    const int n = 100, trials = 100000;
    std::vector<int> rank(n);
    std::iota(rank.begin(), rank.end(), 1);
    std::mt19937 rng(42);
    long long total = 0;
    for (int t = 0; t < trials; ++t) total += hireCount(rank, rng);
    double Hn = 0;
    for (int k = 1; k <= n; ++k) Hn += 1.0 / k;
    std::cout << "模擬平均雇用次數 = " << static_cast<double>(total) / trials
              << "（理論值 H_" << n << " = " << Hn << "）\n";
    return 0;
}
