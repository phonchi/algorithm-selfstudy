// KMP 字串比對（CLRS §32.4）：前綴函數 π ＋ O(n) 掃描
#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefixFunction(const std::string& P) {
    int m = P.size();
    std::vector<int> pi(m + 1, 0);                 // 1-indexed：pi[q] = 最長真前綴長
    int k = 0;
    for (int q = 2; q <= m; ++q) {
        while (k > 0 && P[k] != P[q - 1]) k = pi[k];
        if (P[k] == P[q - 1]) ++k;
        pi[q] = k;
    }
    return pi;
}

int main() {
    std::string T = "abababacaba", P = "ababaca";
    auto pi = prefixFunction(P);
    std::cout << "π(ababaca) = [";
    for (size_t q = 1; q < pi.size(); ++q) std::cout << pi[q] << (q + 1 < pi.size() ? " " : "]\n");

    int n = T.size(), m = P.size(), q = 0;         // q = 已匹配的字元數
    for (int i = 0; i < n; ++i) {
        while (q > 0 && P[q] != T[i]) q = pi[q];   // 失配：退到 π[q]，不回頭讀 T
        if (P[q] == T[i]) ++q;
        if (q == m) {
            std::cout << "在 shift " << i - m + 1 << " 找到 pattern\n";
            q = pi[q];
        }
    }
    return 0;
}
