// counting_sort.cpp — CLRS 4e §8.2（穩定版：從後往前放）
#include <iostream>
#include <vector>

std::vector<int> countingSort(const std::vector<int>& A, int k) {
    std::vector<int> C(k + 1, 0), B(A.size());
    for (int a : A) ++C[a];                        // C[v] = 值 v 出現次數
    for (int v = 1; v <= k; ++v) C[v] += C[v - 1]; // C[v] = 「≤ v」的元素個數
    for (int i = static_cast<int>(A.size()) - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i];                     // 從後往前掃 → 相等元素保持相對順序（穩定）
        --C[A[i]];
    }
    return B;
}

int main() {
    std::vector<int> A = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};   // CLRS 圖 8.2
    for (int x : countingSort(A, 6)) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}
