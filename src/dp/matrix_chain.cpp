// 矩陣鏈乘法（CLRS §14.2）：MATRIX-CHAIN-ORDER＋PRINT-OPTIMAL-PARENS
// 課本例 p = <30,35,15,5,10,20,25> → m[1][6] = 15125
#include <iostream>
#include <string>
#include <vector>

const long long INF = 1e18;
std::vector<std::vector<int>> s;

std::string parens(int i, int j) {
    if (i == j) return "A" + std::to_string(i);
    return "(" + parens(i, s[i][j]) + parens(s[i][j] + 1, j) + ")";
}

int main() {
    std::vector<long long> p = {30, 35, 15, 5, 10, 20, 25};
    int n = p.size() - 1;                            // 6 個矩陣
    std::vector<std::vector<long long>> m(n + 1, std::vector<long long>(n + 1, 0));
    s.assign(n + 1, std::vector<int>(n + 1, 0));

    for (int len = 2; len <= n; ++len)               // 區間長度由小到大
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            m[i][j] = INF;
            for (int k = i; k < j; ++k) {            // 枚舉最後一次相乘的切點
                long long q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) { m[i][j] = q; s[i][j] = k; }
            }
        }

    std::cout << "m 表（上三角，對角線 0 略）：\n";
    for (int len = 2; len <= n; ++len) {
        std::cout << "  長度 " << len << "：";
        for (int i = 1; i + len - 1 <= n; ++i)
            std::cout << "m[" << i << "][" << i + len - 1 << "]=" << m[i][i + len - 1] << " ";
        std::cout << "\n";
    }
    std::cout << "最少乘法次數 m[1][" << n << "] = " << m[1][n] << "\n";
    std::cout << "最佳括號化：" << parens(1, n) << "\n";
    return 0;
}
