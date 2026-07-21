// 開放定址（CLRS §11.4）：linear probing vs double hashing 的探測次數對決
// m = 11（質數），同一批鍵；再示範 DELETED 墓碑為何必要
#include <iostream>
#include <vector>

const int EMPTY = -1, DELETED = -2;
const int M = 11;

int probeInsert(std::vector<int>& T, int k, bool useDouble, int& probes) {
    int h1 = k % M;
    int h2 = useDouble ? 1 + (k % (M - 1)) : 1;      // linear = 步距固定 1
    for (int i = 0; i < M; ++i) {
        int s = (h1 + i * h2) % M;
        ++probes;
        if (T[s] == EMPTY || T[s] == DELETED) { T[s] = k; return s; }
    }
    return -1;                                        // 表滿
}

bool probeSearch(const std::vector<int>& T, int k, bool useDouble) {
    int h1 = k % M, h2 = useDouble ? 1 + (k % (M - 1)) : 1;
    for (int i = 0; i < M; ++i) {
        int s = (h1 + i * h2) % M;
        if (T[s] == k) return true;
        if (T[s] == EMPTY) return false;              // 空格 = 確定不在；DELETED 要繼續
    }
    return false;
}

int main() {
    std::vector<int> keys = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    for (bool dbl : {false, true}) {
        std::vector<int> T(M, EMPTY);
        int probes = 0;
        for (int k : keys) probeInsert(T, k, dbl, probes);
        std::cout << (dbl ? "double hashing" : "linear probing") << "：表 = ";
        for (int v : T) std::cout << (v == EMPTY ? std::string("·") : std::to_string(v)) << ' ';
        std::cout << "｜總探測 " << probes << " 次\n";
    }

    // DELETED 墓碑示範（linear probing）：22 與 55 都雜湊到 slot 0
    std::vector<int> T(M, EMPTY);
    int p = 0;
    probeInsert(T, 22, false, p);                     // 22 → slot 0
    probeInsert(T, 55, false, p);                     // 55 → 碰撞，落 slot 1
    T[22 % M] = DELETED;                              // 刪 22：標記墓碑而非清空
    std::cout << "刪 22 後 search(55)（墓碑版）= " << probeSearch(T, 55, false) << "\n";
    T[22 % M] = EMPTY;                                // 錯誤示範：直接清空
    std::cout << "若直接清空 slot，search(55) = " << probeSearch(T, 55, false)
              << "（探測在空格提前停止 → 找不到還在表裡的 55！）\n";
    return 0;
}
