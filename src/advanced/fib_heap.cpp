// Fibonacci heap（CLRS 4e 線上章節）：精簡版——INSERT / EXTRACT-MIN（CONSOLIDATE）
// / DECREASE-KEY（cut＋cascading cut）。示範懶惰哲學與攤還成本表。
#include <cmath>
#include <iostream>
#include <vector>

struct Node {
    int key, degree = 0;
    bool mark = false;
    Node *p = nullptr, *child = nullptr, *left, *right;
    explicit Node(int k) : key(k) { left = right = this; }
};

struct FibHeap {
    Node* mn = nullptr;
    int n = 0;

    static void listInsert(Node*& root, Node* x) {   // 接進環狀串列
        if (!root) { root = x; x->left = x->right = x; return; }
        x->right = root->right; x->left = root;
        root->right->left = x; root->right = x;
    }
    static void listRemove(Node* x) {
        x->left->right = x->right; x->right->left = x->left;
    }

    void insert(int k) {                     // O(1)：只是接進根串列
        Node* x = new Node(k);
        listInsert(mn, x);
        if (x->key < mn->key) mn = x;
        ++n;
    }
    void link(Node* y, Node* x) {            // y 掛到 x 下（degree 合併）
        listRemove(y);
        y->p = x; y->mark = false;
        y->left = y->right = y;
        listInsert(x->child, y);
        ++x->degree;
    }
    int extractMin() {                       // O(lg n) 攤還：這裡才「整理」
        Node* z = mn;
        int out = z->key;
        if (z->child) {                      // 孩子全部升上根串列
            Node* c = z->child;
            std::vector<Node*> kids;
            Node* cur = c;
            do { kids.push_back(cur); cur = cur->right; } while (cur != c);
            for (Node* k : kids) { k->p = nullptr; listInsert(mn, k); }
        }
        listRemove(z);
        if (z == z->right) mn = nullptr;
        else { mn = z->right; consolidate(); }
        --n; delete z;
        return out;
    }
    void consolidate() {                     // 同 degree 樹兩兩合併
        int D = (int)(std::log2(n)) + 2;
        std::vector<Node*> A(D + 1, nullptr);
        std::vector<Node*> roots;
        Node* cur = mn;
        do { roots.push_back(cur); cur = cur->right; } while (cur != mn);
        for (Node* w : roots) {
            Node* x = w;
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (y->key < x->key) std::swap(x, y);
                link(y, x);
                A[d] = nullptr; ++d;
            }
            A[d] = x;
        }
        mn = nullptr;
        for (Node* a : A)
            if (a) {
                a->left = a->right = a;
                listInsert(mn, a);
                if (a->key < mn->key) mn = a;
            }
    }
    void cut(Node* x, Node* y) {             // x 從 y 剪下、丟回根串列
        if (x->right == x) y->child = nullptr;
        else { if (y->child == x) y->child = x->right; listRemove(x); }
        --y->degree;
        x->left = x->right = x;
        listInsert(mn, x);
        x->p = nullptr; x->mark = false;
    }
    void cascadingCut(Node* y) {             // 失去第二個孩子的節點也被剪
        Node* z = y->p;
        if (!z) return;
        if (!y->mark) y->mark = true;
        else { cut(y, z); cascadingCut(z); }
    }
    void decreaseKey(Node* x, int k) {       // O(1) 攤還：剪下丟回根串列
        x->key = k;
        Node* y = x->p;
        if (y && x->key < y->key) { cut(x, y); cascadingCut(y); }
        if (x->key < mn->key) mn = x;
    }
    Node* findNode(Node* root, int k) {      // 示範用的搜尋（實務由呼叫端持有指標）
        if (!root) return nullptr;
        Node* cur = root;
        do {
            if (cur->key == k) return cur;
            Node* got = findNode(cur->child, k);
            if (got) return got;
            cur = cur->right;
        } while (cur != root);
        return nullptr;
    }
};

int main() {
    FibHeap H;
    for (int k : {23, 7, 21, 3, 18, 39, 52, 38, 41, 17}) H.insert(k);
    std::cout << "INSERT ×10（全掛根串列，O(1) 各自）：n = " << H.n << "\n";
    std::cout << "EXTRACT-MIN = " << H.extractMin()
              << "（此刻才 CONSOLIDATE：同 degree 樹合併）\n";
    Node* x = H.findNode(H.mn, 39);
    H.decreaseKey(x, 1);                     // 39 → 1：cut 丟回根串列
    std::cout << "DECREASE-KEY(39 → 1) 後 MINIMUM = " << H.mn->key << "\n";
    std::cout << "依序 EXTRACT-MIN：";
    while (H.n) std::cout << H.extractMin() << " ";
    std::cout << "\n（= 全部鍵排序：懶歸懶，正確性一分不少）\n";
    return 0;
}
