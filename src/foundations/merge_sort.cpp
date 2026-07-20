// merge_sort.cpp — CLRS 4e §2.3（索引改為 0-based，閉區間 [p, r]）
#include <iostream>
#include <vector>

void merge(std::vector<int>& A, int p, int q, int r) {
    std::vector<int> L(A.begin() + p, A.begin() + q + 1);   // A[p..q]
    std::vector<int> R(A.begin() + q + 1, A.begin() + r + 1); // A[q+1..r]
    std::size_t i = 0, j = 0;
    int k = p;
    while (i < L.size() && j < R.size())
        A[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];   // 取兩疊頂端較小者
    while (i < L.size()) A[k++] = L[i++];
    while (j < R.size()) A[k++] = R[j++];
}

void mergeSort(std::vector<int>& A, int p, int r) {
    if (p >= r) return;                 // 0 或 1 個元素：已排序
    int q = (p + r) / 2;
    mergeSort(A, p, q);                 // Divide + Conquer 左半
    mergeSort(A, q + 1, r);             // Conquer 右半
    merge(A, p, q, r);                  // Combine
}

int main() {
    std::vector<int> A = {12, 3, 7, 9, 14, 6, 11, 2};
    mergeSort(A, 0, static_cast<int>(A.size()) - 1);
    for (int x : A) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}
