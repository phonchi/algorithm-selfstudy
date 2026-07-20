// lcs.cpp — CLRS 4e §14.4：LCS 長度表＋回溯重建
#include <iostream>
#include <string>
#include <vector>

std::string lcs(const std::string& X, const std::string& Y) {
    std::size_t m = X.size(), n = Y.size();
    std::vector<std::vector<int>> c(m + 1, std::vector<int>(n + 1, 0));
    for (std::size_t i = 1; i <= m; ++i)
        for (std::size_t j = 1; j <= n; ++j)
            c[i][j] = (X[i-1] == Y[j-1]) ? c[i-1][j-1] + 1                // ↖ 配對
                                         : std::max(c[i-1][j], c[i][j-1]); // ↑ 或 ←
    std::string out;                       // 從 c[m][n] 反向走回去重建
    for (std::size_t i = m, j = n; i > 0 && j > 0;) {
        if (X[i-1] == Y[j-1]) { out = X[i-1] + out; --i; --j; }
        else if (c[i-1][j] >= c[i][j-1]) --i;
        else --j;
    }
    std::cout << "LCS 長度 = " << c[m][n] << '\n';
    return out;
}

int main() {
    // CLRS §14.4 的例子
    std::cout << lcs("ABCBDAB", "BDCABA") << '\n';
    return 0;
}
