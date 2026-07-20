// quicksort.cpp — CLRS 4e Ch7（Lomuto partition＋隨機化版本）
#include <iostream>
#include <random>
#include <vector>

int partition(std::vector<int>& A, int p, int r) {
    int x = A[r];                       // pivot 取最後一個元素
    int i = p - 1;                      // 「≤ x 區」的右邊界
    for (int j = p; j < r; ++j)
        if (A[j] <= x) std::swap(A[++i], A[j]);
    std::swap(A[i + 1], A[r]);          // pivot 歸位
    return i + 1;
}

int randomizedPartition(std::vector<int>& A, int p, int r, std::mt19937& rng) {
    std::uniform_int_distribution<int> d(p, r);
    std::swap(A[d(rng)], A[r]);         // 隨機挑 pivot 換到尾端
    return partition(A, p, r);
}

void randomizedQuicksort(std::vector<int>& A, int p, int r, std::mt19937& rng) {
    if (p >= r) return;
    int q = randomizedPartition(A, p, r, rng);
    randomizedQuicksort(A, p, q - 1, rng);   // pivot 已在正確位置，不再參與
    randomizedQuicksort(A, q + 1, r, rng);
}

int main() {
    std::vector<int> A = {2, 8, 7, 1, 3, 5, 6, 4};   // CLRS 圖 7.1 的例子
    std::mt19937 rng(7);
    randomizedQuicksort(A, 0, static_cast<int>(A.size()) - 1, rng);
    for (int x : A) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}
