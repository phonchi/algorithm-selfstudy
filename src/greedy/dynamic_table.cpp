// 動態表格（CLRS §16.4）：只擴不縮，滿了加倍。印每次 INSERT 的
// 實際成本 / num / size / Φ = 2·num − size / 攤還成本（= 實際 + ΔΦ）
#include <iomanip>
#include <iostream>

int main() {
    int num = 0, size = 0;
    int phi = 0;                                 // Φ = 2·num − size
    std::cout << " i  實際成本  num  size   Φ   攤還(=實際+ΔΦ)\n";
    for (int i = 1; i <= 16; ++i) {
        int cost;
        if (num == size) {                       // 滿了：加倍搬家（0 → 1）
            int newSize = (size == 0) ? 1 : 2 * size;
            cost = num + 1;                      // 搬 num 個＋插入自己
            size = newSize;
        } else {
            cost = 1;                            // 直接插入
        }
        ++num;
        int newPhi = 2 * num - size;
        int amortized = cost + (newPhi - phi);
        std::cout << std::setw(2) << i << std::setw(8) << cost
                  << std::setw(6) << num << std::setw(6) << size
                  << std::setw(5) << newPhi << std::setw(10) << amortized << "\n";
        phi = newPhi;
    }
    return 0;
}
