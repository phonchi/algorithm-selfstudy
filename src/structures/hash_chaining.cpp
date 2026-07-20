// hash_chaining.cpp — CLRS 4e §11.2 chaining（除法 hash：h(k) = k mod m）
#include <iostream>
#include <list>
#include <vector>

class ChainedHashTable {
    std::vector<std::list<int>> T;
    std::size_t m;
public:
    explicit ChainedHashTable(std::size_t slots) : T(slots), m(slots) {}
    std::size_t h(int k) const { return static_cast<std::size_t>(k) % m; }
    void insert(int k) { T[h(k)].push_front(k); }          // O(1)
    bool search(int k) const {                              // 期望 O(1 + α)
        for (int x : T[h(k)]) if (x == k) return true;
        return false;
    }
    void remove(int k) { T[h(k)].remove(k); }
    void dump() const {
        for (std::size_t s = 0; s < m; ++s) {
            std::cout << s << ':';
            for (int x : T[s]) std::cout << ' ' << x;
            std::cout << '\n';
        }
    }
};

int main() {
    ChainedHashTable H(9);
    for (int k : {5, 28, 19, 15, 20, 33, 12, 17, 10})   // CLRS 練習 11.2-2 的鍵
        H.insert(k);
    H.dump();
    std::cout << "search(20) = " << H.search(20)
              << ", search(21) = " << H.search(21) << '\n';
    return 0;
}
