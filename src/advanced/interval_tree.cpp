// 區間樹（CLRS §17.3）：BST（鍵=low）＋ max 欄位（子樹最大右端點）
// 示範版掛在未平衡 BST 上聚焦 max 欄位；課本掛紅黑樹保 O(lg n)
#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
    int lo, hi, mx;
    Node *l = nullptr, *r = nullptr;
    Node(int a, int b) : lo(a), hi(b), mx(b) {}
};

Node* insert(Node* x, int lo, int hi) {
    if (!x) return new Node(lo, hi);
    if (lo < x->lo) x->l = insert(x->l, lo, hi);
    else x->r = insert(x->r, lo, hi);
    x->mx = std::max(x->mx, hi);                 // 沿路維護 max
    return x;
}

Node* intervalSearch(Node* x, int lo, int hi) {  // 找任一與 [lo, hi] 重疊的區間
    while (x && (x->hi < lo || hi < x->lo)) {    // 不重疊才繼續走
        if (x->l && x->l->mx >= lo) x = x->l;    // 左子樹可能有解 → 往左
        else x = x->r;                           // 否則左子樹必無解 → 往右
    }
    return x;
}

int main() {
    std::vector<std::pair<int,int>> iv = {{16,21},{8,9},{25,30},{5,8},{15,23},
                                          {17,19},{26,26},{0,3},{6,10},{19,20}};
    Node* root = nullptr;                        // CLRS 圖 17.4 的十個區間
    for (auto [a, b] : iv) root = insert(root, a, b);

    for (auto [a, b] : std::vector<std::pair<int,int>>{{22,25},{11,14}}) {
        Node* hit = intervalSearch(root, a, b);
        std::cout << "SEARCH([" << a << "," << b << "]) = ";
        if (hit) std::cout << "[" << hit->lo << "," << hit->hi << "]\n";
        else std::cout << "NIL（無重疊區間）\n";
    }
    return 0;
}
