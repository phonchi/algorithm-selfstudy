// APPROX-VERTEX-COVER：CLRS 圖 35.1，2-近似（實跑得 6 顆，最佳解 3 顆）
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

int main() {
    const std::string name = "abcdefg";
    std::vector<std::pair<int,int>> E = {{0,1},{1,2},{2,3},{2,4},{3,4},{3,5},{3,6},{4,5}};
    std::set<int> C;
    std::vector<bool> dead(E.size(), false);

    for (size_t i = 0; i < E.size(); ++i) {
        if (dead[i]) continue;
        auto [u, v] = E[i];                       // 任取一條還活著的邊
        C.insert(u); C.insert(v);                 // 兩端點都收
        std::cout << "選邊 (" << name[u] << ", " << name[v] << ")，蓋掉：";
        for (size_t j = 0; j < E.size(); ++j)     // 刪掉碰到 u 或 v 的所有邊
            if (!dead[j] && (E[j].first == u || E[j].first == v ||
                             E[j].second == u || E[j].second == v)) {
                dead[j] = true;
                std::cout << name[E[j].first] << "-" << name[E[j].second] << " ";
            }
        std::cout << "\n";
    }
    std::cout << "cover = { ";
    for (int v : C) std::cout << name[v] << " ";
    std::cout << "}，|C| = " << C.size() << "（最佳解 {b, d, e} 只要 3——比值 2 以內）\n";
    return 0;
}
