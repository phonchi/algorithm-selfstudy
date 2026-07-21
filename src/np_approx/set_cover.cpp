// 貪婪集合覆蓋（CLRS §35.3）：每輪選「蓋最多未蓋元素」的集合；H(max|S|) 近似
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::set<int>>> F = {
        {"S1", {1,2,3,4,5,6}}, {"S2", {5,6,8,9}}, {"S3", {1,4,7,10}},
        {"S4", {2,5,7,8,11}},  {"S5", {3,6,9,12}}, {"S6", {10,11}}};
    std::set<int> U;
    for (int i = 1; i <= 12; ++i) U.insert(i);      // CLRS 圖 35.3

    std::vector<std::string> cover;
    while (!U.empty()) {
        std::size_t best = 0, bestGain = 0;
        for (std::size_t i = 0; i < F.size(); ++i) {
            std::size_t gain = 0;
            for (int e : F[i].second) gain += U.count(e);
            if (gain > bestGain) { bestGain = gain; best = i; }
        }
        for (int e : F[best].second) U.erase(e);
        cover.push_back(F[best].first);
        std::cout << "選 " << F[best].first << "（新蓋 " << bestGain
                  << " 個），剩 " << U.size() << " 個未蓋\n";
    }
    std::cout << "貪婪覆蓋共 " << cover.size() << " 個：";
    for (const auto& s : cover) std::cout << s << " ";
    std::cout << "（最佳 {S3,S4,S5} 只要 3 個）\n";
    return 0;
}
