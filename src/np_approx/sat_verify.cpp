// NP 的「驗證」視角：給一張證書（賦值），O(公式長度) 就能檢查 3-CNF 是否滿足
#include <iostream>
#include <vector>

int main() {
    // (x1 ∨ ¬x2 ∨ x3) ∧ (¬x1 ∨ x2 ∨ x4) ∧ (¬x3 ∨ ¬x4 ∨ x2)
    // 文字用帶號整數表示：+i = xi、-i = ¬xi
    std::vector<std::vector<int>> clauses = {{1,-2,3}, {-1,2,4}, {-3,-4,2}};
    std::vector<bool> cert = {false, true, true, false, false};  // 證書：x1=T x2=T x3=F x4=F（cert[0] 不用）

    bool all = true;
    for (const auto& cl : clauses) {
        bool sat = false;
        for (int lit : cl) {
            int v = lit > 0 ? lit : -lit;
            if ((lit > 0) == cert[v]) sat = true;   // 文字為真
        }
        std::cout << "子句 (";
        for (size_t i = 0; i < cl.size(); ++i)
            std::cout << (cl[i] < 0 ? "!x" : "x") << (cl[i] < 0 ? -cl[i] : cl[i])
                      << (i + 1 < cl.size() ? " | " : "");
        std::cout << ") = " << (sat ? "true" : "false") << "\n";
        all = all && sat;
    }
    std::cout << "證書 x1=T, x2=T, x3=F, x4=F 驗證結果：" << (all ? "滿足" : "不滿足")
              << "（掃一遍公式，線性時間）\n";
    return 0;
}
