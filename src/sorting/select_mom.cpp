// 最壞情況線性 SELECT（CLRS §9.3 中位數之中位數）
#include <algorithm>
#include <iostream>
#include <vector>

int select(std::vector<int> A, int i) {          // 第 i 小（1-based），最壞 O(n)
    if (A.size() <= 5) {
        std::sort(A.begin(), A.end());
        return A[i - 1];
    }
    std::vector<int> medians;                    // ① 5 個一組取各組中位數
    for (std::size_t j = 0; j < A.size(); j += 5) {
        auto e = std::min(j + 5, A.size());
        std::vector<int> g(A.begin() + j, A.begin() + e);
        std::sort(g.begin(), g.end());
        medians.push_back(g[g.size() / 2]);
    }
    int x = select(medians, (medians.size() + 1) / 2);   // ② 中位數們的中位數
    std::vector<int> lo, eq, hi;                 // ③ 三路分割
    for (int a : A) (a < x ? lo : a == x ? eq : hi).push_back(a);
    if (i <= (int)lo.size()) return select(lo, i);
    if (i <= (int)(lo.size() + eq.size())) return x;
    return select(hi, i - lo.size() - eq.size());
}

int main() {
    std::vector<int> A = {3, 2, 9, 0, 7, 5, 4, 8, 6, 1, 12, 11, 10, 14, 13};
    std::cout << "第 8 小（中位數）= " << select(A, 8) << "\n";
    std::cout << "第 1 小 = " << select(A, 1)
              << "，第 15 小 = " << select(A, 15) << "\n";
    return 0;
}
