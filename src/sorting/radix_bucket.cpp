// radix sort（CLRS 圖 8.3 例，逐位穩定 counting sort）＋ bucket sort（圖 8.4 例）
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

void countingByDigit(std::vector<int>& A, int exp) {   // 依第 exp 位穩定排序
    std::vector<int> C(10, 0), B(A.size());
    for (int a : A) ++C[(a / exp) % 10];
    for (int v = 1; v < 10; ++v) C[v] += C[v - 1];
    for (int i = (int)A.size() - 1; i >= 0; --i) {     // 從後往前 → 穩定
        int d = (A[i] / exp) % 10;
        B[--C[d]] = A[i];
    }
    A = B;
}

int main() {
    std::vector<int> A = {329, 457, 657, 839, 436, 720, 355};
    for (int exp = 1; exp <= 100; exp *= 10) {
        countingByDigit(A, exp);
        std::cout << "依 " << std::setw(3) << exp << " 位排完：";
        for (int a : A) std::cout << a << ' ';
        std::cout << "\n";
    }

    // bucket sort：均勻分布於 [0,1)，n 個桶、各桶 insertion sort（此處用 std::sort 示意）
    std::vector<double> X = {.78, .17, .39, .26, .72, .94, .21, .12, .23, .68};
    int n = X.size();
    std::vector<std::vector<double>> bucket(n);
    for (double x : X) bucket[(int)(n * x)].push_back(x);   // ⌊n·x⌋ 號桶
    std::cout << "bucket sort：";
    for (auto& b : bucket) {
        std::sort(b.begin(), b.end());
        for (double x : b) std::cout << x << ' ';
    }
    std::cout << "\n";
    return 0;
}
