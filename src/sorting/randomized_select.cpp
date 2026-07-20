// randomized_select.cpp — CLRS 4e §9.2：期望線性時間找第 i 小
#include <iostream>
#include <random>
#include <vector>

int partition(std::vector<int>& A, int p, int r) {
    int x = A[r], i = p - 1;
    for (int j = p; j < r; ++j)
        if (A[j] <= x) std::swap(A[++i], A[j]);
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

// 回傳 A[p..r] 中第 i 小（i 從 1 起算）
int randomizedSelect(std::vector<int>& A, int p, int r, int i, std::mt19937& rng) {
    if (p == r) return A[p];
    std::uniform_int_distribution<int> d(p, r);
    std::swap(A[d(rng)], A[r]);
    int q = partition(A, p, r);
    int k = q - p + 1;                  // pivot 在這段裡排第 k 小
    if (i == k) return A[q];            // 運氣好：pivot 就是答案
    if (i < k) return randomizedSelect(A, p, q - 1, i, rng);          // 只走一邊！
    return randomizedSelect(A, q + 1, r, i - k, rng);
}

int main() {
    std::vector<int> A = {3, 2, 9, 0, 7, 5, 4, 8, 6, 1};
    std::mt19937 rng(9);
    for (int i : {1, 5, 10}) {
        std::vector<int> tmp = A;
        std::cout << "第 " << i << " 小 = "
                  << randomizedSelect(tmp, 0, static_cast<int>(tmp.size()) - 1, i, rng) << '\n';
    }
    return 0;
}
