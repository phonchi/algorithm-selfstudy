// 擴充資料結構（CLRS Ch17）：BST 加掛 size 欄位 → OS-SELECT / OS-RANK
// 課本掛在紅黑樹上以保證 O(lg n)；這裡用未平衡 BST 聚焦「size 欄位怎麼用」。
#include <iostream>
#include <vector>

struct Node {
    int key, size = 1;
    Node *l = nullptr, *r = nullptr, *p = nullptr;
    Node(int k) : key(k) {}
};
int sz(Node* x) { return x ? x->size : 0; }

void insert(Node* root, int k) {
    Node* x = root;
    while (true) {
        ++x->size;                                 // 沿路每個節點 size + 1
        Node*& c = k < x->key ? x->l : x->r;
        if (!c) { c = new Node(k); c->p = x; return; }
        x = c;
    }
}

Node* osSelect(Node* x, int i) {                   // 第 i 小
    int r = sz(x->l) + 1;                          // x 在自己子樹中的名次
    if (i == r) return x;
    return i < r ? osSelect(x->l, i) : osSelect(x->r, i - r);
}

int osRank(Node* root, Node* x) {                  // x 的整體名次
    int r = sz(x->l) + 1;
    for (Node* y = x; y != root; y = y->p)
        if (y == y->p->r) r += sz(y->p->l) + 1;    // 右孩子：加左兄弟子樹＋父
    return r;
}

int main() {
    std::vector<int> keys = {26,17,41,14,21,30,47,10,16,19,20,28,38,7,12,3,35,39};
    Node* root = nullptr;
    for (int k : keys) {
        if (!root) root = new Node(k);
        else insert(root, k);
    }
    Node* n10 = osSelect(root, 10);
    std::cout << "OS-SELECT(root, 10) = " << n10->key << "（第 10 小的鍵）\n";
    Node* x = root;
    while (x->key != 38) x = 38 < x->key ? x->l : x->r;
    std::cout << "OS-RANK(38) = " << osRank(root, x) << "\n";
    std::cout << "root 的 size = " << root->size << "（= 全部 " << keys.size() << " 個鍵）\n";
    return 0;
}
