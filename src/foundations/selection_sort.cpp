// selection sort（CLRS 習題 2.2-2）：每輪從 A[i..n-1] 挑最小值換到 A[i]，
// 印出每輪結束的陣列狀態——觀察「前綴不只有序，還是全域最小的那批」
#include <algorithm>
#include <iostream>
#include <vector>

void selectionSort(std::vector<int>& A) {
    for (std::size_t i = 0; i + 1 < A.size(); ++i) {   // 只需 n-1 輪：最後一格自動就位
        std::size_t m = i;
        for (std::size_t j = i + 1; j < A.size(); ++j)
            if (A[j] < A[m]) m = j;                    // 線性掃出 A[i..n-1] 的最小值
        std::swap(A[i], A[m]);
        for (int v : A) std::cout << v << ' ';
        std::cout << " （前 " << i + 1 << " 格已定案）\n";
    }
}

int main() {
    std::vector<int> A = {5, 2, 4, 6, 1, 3};
    selectionSort(A);
    return 0;
}
