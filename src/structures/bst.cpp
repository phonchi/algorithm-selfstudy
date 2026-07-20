// bst.cpp — CLRS 4e Ch12：BST 插入／搜尋／走訪／刪除（transplant 版）
#include <iostream>

struct Node {
    int key;
    Node *left = nullptr, *right = nullptr, *p = nullptr;
    explicit Node(int k) : key(k) {}
};

struct BST {
    Node* root = nullptr;

    void insert(int k) {                       // TREE-INSERT：沿途二選一往下走
        Node* z = new Node(k);
        Node *y = nullptr, *x = root;
        while (x) { y = x; x = (k < x->key) ? x->left : x->right; }
        z->p = y;
        if (!y) root = z;
        else if (k < y->key) y->left = z;
        else y->right = z;
    }
    Node* search(Node* x, int k) const {
        while (x && x->key != k) x = (k < x->key) ? x->left : x->right;
        return x;
    }
    Node* minimum(Node* x) const { while (x->left) x = x->left; return x; }

    void transplant(Node* u, Node* v) {        // 用 v 的子樹取代 u 的位置
        if (!u->p) root = v;
        else if (u == u->p->left) u->p->left = v;
        else u->p->right = v;
        if (v) v->p = u->p;
    }
    void erase(Node* z) {                      // TREE-DELETE 三情境
        if (!z->left) transplant(z, z->right);
        else if (!z->right) transplant(z, z->left);
        else {
            Node* y = minimum(z->right);       // 後繼：右子樹最小
            if (y->p != z) {
                transplant(y, y->right);
                y->right = z->right; y->right->p = y;
            }
            transplant(z, y);
            y->left = z->left; y->left->p = y;
        }
        delete z;
    }
    void inorder(Node* x) const {
        if (!x) return;
        inorder(x->left);
        std::cout << x->key << ' ';
        inorder(x->right);
    }
};

int main() {
    BST T;
    for (int k : {12, 5, 18, 2, 9, 15, 19, 17}) T.insert(k);
    T.inorder(T.root); std::cout << '\n';
    T.erase(T.search(T.root, 12));             // 刪除有兩個子節點的根
    T.inorder(T.root); std::cout << '\n';
    std::cout << "min = " << T.minimum(T.root)->key << '\n';
    return 0;
}
