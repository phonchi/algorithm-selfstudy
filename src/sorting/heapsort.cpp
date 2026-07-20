// heapsort.cpp — CLRS 4e Ch6（0-based：left = 2i+1, right = 2i+2）
#include <iostream>
#include <vector>

void maxHeapify(std::vector<int>& A, int heapSize, int i) {
    int l = 2 * i + 1, r = 2 * i + 2, largest = i;
    if (l < heapSize && A[l] > A[largest]) largest = l;
    if (r < heapSize && A[r] > A[largest]) largest = r;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        maxHeapify(A, heapSize, largest);   // 被換下去的值繼續往下沉
    }
}

void buildMaxHeap(std::vector<int>& A) {
    // 葉節點天然是 heap：從最後一個內部節點往前整理
    for (int i = static_cast<int>(A.size()) / 2 - 1; i >= 0; --i)
        maxHeapify(A, static_cast<int>(A.size()), i);
}

void heapSort(std::vector<int>& A) {
    buildMaxHeap(A);
    for (int i = static_cast<int>(A.size()) - 1; i >= 1; --i) {
        std::swap(A[0], A[i]);        // 最大值歸位到尾端
        maxHeapify(A, i, 0);          // heap 縮小一格後修復
    }
}

int main() {
    std::vector<int> A = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};   // CLRS 圖 6.4 已建堆
    std::vector<int> B = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};   // CLRS 圖 6.3 原始輸入
    heapSort(A); heapSort(B);
    for (int x : A) std::cout << x << ' ';
    std::cout << '\n';
    for (int x : B) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}
