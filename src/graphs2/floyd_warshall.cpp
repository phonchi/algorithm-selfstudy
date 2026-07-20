// Floyd-Warshall：CLRS 圖 23.1 的 5 頂點有向圖，D^(5) 與書中圖 23.4 相同
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const int n = 5, INF = 1e9;
    std::vector<std::vector<int>> d = {
        {  0,   3,   8, INF,  -4},
        {INF,   0, INF,   1,   7},
        {INF,   4,   0, INF, INF},
        {  2, INF,  -5,   0, INF},
        {INF, INF, INF,   6,   0}};

    for (int k = 0; k < n; ++k)              // 中繼點只能用 {1..k}
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

    std::cout << "D（所有點對最短路徑權重）：\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) std::cout << std::setw(4) << d[i][j];
        std::cout << "\n";
    }
    return 0;
}
