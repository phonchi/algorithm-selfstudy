// rb_tree.cpp — CLRS 4e Ch13：red-black tree 插入（旋轉＋INSERT-FIXUP）
#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int key; Color color;
    Node *left, *right, *p;
};

struct RBTree {
    Node* nil;                                  // 哨兵：所有葉子與 root 的父母
    Node* root;
    RBTree() {
        nil = new Node{0, BLACK, nullptr, nullptr, nullptr};
        root = nil;
    }
    void leftRotate(Node* x) {                  // x 的右子 y 升上來，β 過繼給 x
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->p = x;
        y->p = x->p;
        if (x->p == nil) root = y;
        else if (x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->left = x; x->p = y;
    }
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nil) y->right->p = x;
        y->p = x->p;
        if (x->p == nil) root = y;
        else if (x == x->p->right) x->p->right = y;
        else x->p->left = y;
        y->right = x; x->p = y;
    }
    void insert(int k) {
        Node* z = new Node{k, RED, nil, nil, nil};   // 新節點永遠先塗紅
        Node *y = nil, *x = root;
        while (x != nil) { y = x; x = (k < x->key) ? x->left : x->right; }
        z->p = y;
        if (y == nil) root = z;
        else if (k < y->key) y->left = z;
        else y->right = z;
        insertFixup(z);
    }
    void insertFixup(Node* z) {
        while (z->p->color == RED) {
            if (z->p == z->p->p->left) {
                Node* y = z->p->p->right;               // 叔叔
                if (y->color == RED) {                  // Case 1：叔紅 → 變色上推
                    z->p->color = BLACK; y->color = BLACK;
                    z->p->p->color = RED; z = z->p->p;
                } else {
                    if (z == z->p->right) {             // Case 2：內側 → 先轉成外側
                        z = z->p; leftRotate(z);
                    }
                    z->p->color = BLACK;                // Case 3：外側 → 變色＋旋轉
                    z->p->p->color = RED;
                    rightRotate(z->p->p);
                }
            } else {                                    // 鏡像
                Node* y = z->p->p->left;
                if (y->color == RED) {
                    z->p->color = BLACK; y->color = BLACK;
                    z->p->p->color = RED; z = z->p->p;
                } else {
                    if (z == z->p->left) { z = z->p; rightRotate(z); }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    leftRotate(z->p->p);
                }
            }
        }
        root->color = BLACK;                            // 性質 2 收尾
    }
    void transplant(Node* u, Node* v) {         // 用子樹 v 整棵取代 u（v 可為 nil）
        if (u->p == nil) root = v;
        else if (u == u->p->left) u->p->left = v;
        else u->p->right = v;
        v->p = u->p;                            // 哨兵的好處：v == nil 也照設
    }
    Node* minimum(Node* x) const {
        while (x->left != nil) x = x->left;
        return x;
    }
    void deleteKey(int k) {
        Node* z = root;
        while (z != nil && z->key != k) z = (k < z->key) ? z->left : z->right;
        if (z == nil) return;
        Node* y = z;                            // y = 實際被移出/移動的節點
        Color yOrig = y->color;
        Node* x;                                // x = 接手 y 原位置的節點（可能是 nil）
        if (z->left == nil) { x = z->right; transplant(z, z->right); }
        else if (z->right == nil) { x = z->left; transplant(z, z->left); }
        else {
            y = minimum(z->right);              // 後繼（必無左子）
            yOrig = y->color;
            x = y->right;
            if (y->p == z) x->p = y;            // x 可能是 nil，仍要記父母
            else {
                transplant(y, y->right);
                y->right = z->right; y->right->p = y;
            }
            transplant(z, y);
            y->left = z->left; y->left->p = y;
            y->color = z->color;                // y 繼承 z 的顏色 → 上方性質不變
        }
        if (yOrig == BLACK) deleteFixup(x);     // 少了一個黑 → x 帶著「雙黑」修復
    }
    void deleteFixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->p->left) {
                Node* w = x->p->right;                  // 兄弟
                if (w->color == RED) {                  // Case 1：兄紅 → 轉成兄黑
                    w->color = BLACK; x->p->color = RED;
                    leftRotate(x->p); w = x->p->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED; x = x->p;           // Case 2：姪全黑 → 雙黑上推
                } else {
                    if (w->right->color == BLACK) {     // Case 3：遠姪黑 → 轉成 Case 4
                        w->left->color = BLACK; w->color = RED;
                        rightRotate(w); w = x->p->right;
                    }
                    w->color = x->p->color;             // Case 4：遠姪紅 → 借一個黑
                    x->p->color = BLACK; w->right->color = BLACK;
                    leftRotate(x->p);
                    x = root;                           // 修復完成
                }
            } else {                                    // 鏡像
                Node* w = x->p->left;
                if (w->color == RED) {
                    w->color = BLACK; x->p->color = RED;
                    rightRotate(x->p); w = x->p->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED; x = x->p;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK; w->color = RED;
                        leftRotate(w); w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK; w->left->color = BLACK;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = BLACK;                               // 雙黑落地：吸收成單黑
    }
    void inorder(Node* x) const {
        if (x == nil) return;
        inorder(x->left);
        std::cout << x->key << (x->color == RED ? "R " : "B ");
        inorder(x->right);
    }
    // 驗證：回傳黑高度；違反性質時回 -1
    int check(Node* x) const {
        if (x == nil) return 1;
        if (x->color == RED && (x->left->color == RED || x->right->color == RED))
            return -1;                                  // 性質 4：紅節點無紅子
        int hl = check(x->left), hr = check(x->right);
        if (hl < 0 || hr < 0 || hl != hr) return -1;    // 性質 5：黑高度一致
        return hl + (x->color == BLACK ? 1 : 0);
    }
};

int main() {
    RBTree T;
    for (int k : {41, 38, 31, 12, 19, 8})   // CLRS 練習 13.3-2 的插入序列
        T.insert(k);
    T.inorder(T.root); std::cout << '\n';
    std::cout << "root = " << T.root->key
              << ", 性質檢查(黑高度) = " << T.check(T.root) << '\n';
    for (int k : {8, 12, 19, 31, 38, 41}) { // 依序全刪，逐步驗證五性質
        T.deleteKey(k);
        std::cout << "delete " << k << " → ";
        T.inorder(T.root);
        std::cout << "｜check = " << T.check(T.root) << '\n';
    }
    return 0;
}
