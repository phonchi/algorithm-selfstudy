// knapsack.cpp — 0/1 背包（CLRS 4e 練習 14.4；經典 DP 表格）
#include <iostream>
#include <vector>

int knapsack(const std::vector<int>& w, const std::vector<int>& v, int W,
             std::vector<int>& picked) {
    int n = static_cast<int>(w.size());
    // dp[i][c] = 只考慮前 i 件、容量 c 的最大價值
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int c = 0; c <= W; ++c) {
            dp[i][c] = dp[i-1][c];                          // 不拿第 i 件
            if (c >= w[i-1])
                dp[i][c] = std::max(dp[i][c], dp[i-1][c - w[i-1]] + v[i-1]); // 拿
        }
    for (int i = n, c = W; i >= 1; --i)                     // 回溯選了哪些
        if (dp[i][c] != dp[i-1][c]) { picked.push_back(i); c -= w[i-1]; }
    return dp[n][W];
}

int main() {
    std::vector<int> w = {2, 3, 4, 5}, v = {3, 4, 5, 8};   // 重量、價值
    std::vector<int> picked;
    int best = knapsack(w, v, 9, picked);
    std::cout << "W = 9 最大價值 = " << best << "，選物品：";
    for (auto it = picked.rbegin(); it != picked.rend(); ++it) std::cout << *it << ' ';
    std::cout << '\n';
    return 0;
}
