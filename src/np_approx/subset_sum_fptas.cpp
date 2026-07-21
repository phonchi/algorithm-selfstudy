// 子集和 FPTAS（CLRS §35.5）：EXACT-SUBSET-SUM vs APPROX-SUBSET-SUM（TRIM）
#include <iostream>
#include <set>
#include <vector>

std::vector<double> mergeAdd(const std::vector<double>& L, double x, double t) {
    std::set<double> s(L.begin(), L.end());
    for (double v : L)
        if (v + x <= t) s.insert(v + x);            // L ∪ (L ⊕ x)，超過 t 丟掉
    return {s.begin(), s.end()};
}

std::vector<double> trim(const std::vector<double>& L, double delta) {
    std::vector<double> out = {L[0]};
    double last = L[0];
    for (double v : L)
        if (v > last * (1 + delta)) {               // 差距夠大才保留
            out.push_back(v);
            last = v;
        }
    return out;
}

int main() {
    std::vector<double> S = {104, 102, 201, 101};   // CLRS §35.5 的例子
    double t = 308, eps = 0.40;
    int n = S.size();

    std::vector<double> L = {0};                    // EXACT（指數級清單）
    for (double x : S) L = mergeAdd(L, x, t);
    std::cout << "exact  = " << L.back() << "\n";

    std::vector<double> A = {0};                    // APPROX：每輪 TRIM
    for (double x : S) {
        A = mergeAdd(A, x, t);
        A = trim(A, eps / (2 * n));
        std::cout << "處理 " << x << " 後 |L| = " << A.size() << "\n";
    }
    std::cout << "approx = " << A.back()
              << "（比值 " << L.back() / A.back() << " ≤ 1+ε = 1.4）\n";
    return 0;
}
