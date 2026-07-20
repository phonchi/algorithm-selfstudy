// activity_selection.cpp — CLRS 4e §15.1：依結束時間排序後貪婪掃描
#include <algorithm>
#include <iostream>
#include <vector>

struct Activity { int id, s, f; };   // 開始、結束時間

std::vector<int> greedyActivitySelector(std::vector<Activity> acts) {
    std::sort(acts.begin(), acts.end(),
              [](const Activity& a, const Activity& b) { return a.f < b.f; });
    std::vector<int> chosen;
    int lastFinish = 0;
    for (const auto& a : acts)
        if (a.s >= lastFinish) {      // 與已選的最後一個相容 → 選它
            chosen.push_back(a.id);
            lastFinish = a.f;
        }
    return chosen;
}

int main() {
    // CLRS 圖 15.1 的 11 個活動（已按 f 排序）
    std::vector<Activity> acts = {
        {1,1,4},{2,3,5},{3,0,6},{4,5,7},{5,3,9},{6,5,9},
        {7,6,10},{8,7,11},{9,8,12},{10,2,14},{11,12,16}};
    auto chosen = greedyActivitySelector(acts);
    std::cout << "選了 " << chosen.size() << " 個活動：";
    for (int id : chosen) std::cout << 'a' << id << ' ';
    std::cout << '\n';
    return 0;
}
