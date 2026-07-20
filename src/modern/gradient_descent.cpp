// 梯度下降（CLRS 4e §33.3）：最小化 f(x) = (x-3)^2 + 2，學習率的威力與危險
#include <iomanip>
#include <iostream>

int main() {
    auto f  = [](double x) { return (x - 3) * (x - 3) + 2; };
    auto df = [](double x) { return 2 * (x - 3); };           // 梯度

    std::cout << std::fixed << std::setprecision(4);
    for (double eta : {0.1, 0.9, 1.1}) {                       // 三種學習率
        double x = -2;
        std::cout << "η = " << std::setprecision(1) << eta << std::setprecision(4) << "：x = -2.0000";
        for (int t = 1; t <= 30; ++t) {
            x = x - eta * df(x);                               // x ← x − η∇f(x)
            if (t <= 3 || t == 30) std::cout << " → " << x;
            if (t == 3 && t < 30) std::cout << " → …";
            if (std::abs(x) > 1e6) { std::cout << " → 發散！"; break; }
        }
        std::cout << "，f(x) = " << f(x) << "\n";
    }
    std::cout << "η 太小走得慢、剛好收斂快、太大在谷底兩側越盪越遠。\n";
    return 0;
}
