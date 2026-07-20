// cut_rod.cpp — CLRS 4e §14.1：naive（計呼叫數）vs bottom-up
#include <iostream>
#include <vector>

long long calls = 0;

int cutRodNaive(const std::vector<int>& p, int n) {
    ++calls;
    if (n == 0) return 0;
    int q = -1;
    for (int i = 1; i <= n; ++i)
        q = std::max(q, p[i] + cutRodNaive(p, n - i));   // 第一刀切 i，其餘遞迴
    return q;
}

std::pair<int, std::vector<int>> bottomUpCutRod(const std::vector<int>& p, int n) {
    std::vector<int> r(n + 1, 0), s(n + 1, 0);   // r[j] = 長度 j 的最佳收益；s[j] = 第一刀
    for (int j = 1; j <= n; ++j) {
        int q = -1;
        for (int i = 1; i <= j; ++i)
            if (p[i] + r[j - i] > q) { q = p[i] + r[j - i]; s[j] = i; }
        r[j] = q;
    }
    return {r[n], s};
}

int main() {
    // CLRS 圖 14.1 的價格表：p[i] = 長度 i 的售價
    std::vector<int> p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 10;
    int naive = cutRodNaive(p, n);
    auto [best, s] = bottomUpCutRod(p, n);
    std::cout << "naive = " << naive << "（遞迴呼叫 " << calls << " 次 = 2^n）\n";
    std::cout << "bottom-up = " << best << "，切法：";
    while (n > 0) { std::cout << s[n] << ' '; n -= s[n]; }
    std::cout << '\n';
    return 0;
}
