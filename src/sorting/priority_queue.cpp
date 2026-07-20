// 最大優先佇列（CLRS §6.5）：MAXIMUM / EXTRACT-MAX / INCREASE-KEY / INSERT
#include <iostream>
#include <limits>
#include <vector>

void maxHeapify(std::vector<int>& A, int heapSize, int i) {
    int l = 2 * i + 1, r = 2 * i + 2, largest = i;
    if (l < heapSize && A[l] > A[largest]) largest = l;
    if (r < heapSize && A[r] > A[largest]) largest = r;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        maxHeapify(A, heapSize, largest);
    }
}

int heapExtractMax(std::vector<int>& A) {      // O(lg n)：尾補頂、下沉
    int mx = A[0];
    A[0] = A.back();
    A.pop_back();
    maxHeapify(A, A.size(), 0);
    return mx;
}

void heapIncreaseKey(std::vector<int>& A, int i, int key) {   // O(lg n)：上浮
    A[i] = key;
    while (i > 0 && A[(i - 1) / 2] < A[i]) {
        std::swap(A[i], A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void maxHeapInsert(std::vector<int>& A, int key) {  // 先塞 -∞ 佔位再增鍵
    A.push_back(std::numeric_limits<int>::min());
    heapIncreaseKey(A, A.size() - 1, key);
}

void show(const std::vector<int>& A) {
    for (int v : A) std::cout << v << ' ';
    std::cout << "\n";
}

int main() {
    std::vector<int> A = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};   // CLRS 圖 6.5
    maxHeapInsert(A, 15);
    std::cout << "INSERT(15) 後: "; show(A);
    std::cout << "EXTRACT-MAX = " << heapExtractMax(A) << "\n之後: "; show(A);
    return 0;
}
