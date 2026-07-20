// insertion_sort.cpp — CLRS 4e §2.1（索引改為 0-based）
#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& A) {
    for (std::size_t i = 1; i < A.size(); ++i) {
        int key = A[i];
        // 將 key 插入已排序的 A[0..i-1]：把比 key 大的元素右移
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

int main() {
    std::vector<int> A = {5, 2, 4, 6, 1, 3};   // CLRS 圖 2.2 的例子
    insertionSort(A);
    for (int x : A) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}
