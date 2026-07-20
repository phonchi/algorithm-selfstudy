// B-tree（CLRS Ch18）t = 2（2-3-4 樹）：插入含 split-child，逐層印出
#include <iostream>
#include <string>
#include <vector>

const int T = 2;                                   // 最小分支度：鍵數 t-1 ~ 2t-1
struct BNode {
    std::vector<char> keys;
    std::vector<BNode*> ch;
    bool leaf = true;
};

void splitChild(BNode* x, int i) {                 // x->ch[i] 滿（2t-1 鍵）→ 分裂
    BNode* y = x->ch[i];
    BNode* z = new BNode;
    z->leaf = y->leaf;
    char mid = y->keys[T - 1];
    z->keys.assign(y->keys.begin() + T, y->keys.end());
    y->keys.resize(T - 1);
    if (!y->leaf) {
        z->ch.assign(y->ch.begin() + T, y->ch.end());
        y->ch.resize(T);
    }
    x->keys.insert(x->keys.begin() + i, mid);      // 中位鍵上浮
    x->ch.insert(x->ch.begin() + i + 1, z);
    std::cout << "split：" << mid << " 上浮\n";
}

void insertNonfull(BNode* x, char k) {
    int i = x->keys.size() - 1;
    if (x->leaf) {
        x->keys.push_back(0);
        while (i >= 0 && k < x->keys[i]) { x->keys[i + 1] = x->keys[i]; --i; }
        x->keys[i + 1] = k;
    } else {
        while (i >= 0 && k < x->keys[i]) --i;
        ++i;
        if ((int)x->ch[i]->keys.size() == 2 * T - 1) {
            splitChild(x, i);
            if (k > x->keys[i]) ++i;
        }
        insertNonfull(x->ch[i], k);
    }
}

BNode* insert(BNode* root, char k) {
    if ((int)root->keys.size() == 2 * T - 1) {     // 根滿：長高一層（B-tree 唯一長高方式）
        BNode* s = new BNode;
        s->leaf = false;
        s->ch.push_back(root);
        splitChild(s, 0);
        root = s;
    }
    insertNonfull(root, k);
    return root;
}

int main() {
    BNode* root = new BNode;
    for (char k : std::string("FSQKCLHTVWMRN")) root = insert(root, k);
    std::vector<BNode*> level = {root};
    int d = 0;
    while (!level.empty()) {
        std::vector<BNode*> next;
        std::cout << "第 " << d++ << " 層：";
        for (BNode* x : level) {
            std::cout << "[";
            for (size_t i = 0; i < x->keys.size(); ++i)
                std::cout << x->keys[i] << (i + 1 < x->keys.size() ? " " : "");
            std::cout << "] ";
            for (BNode* c : x->ch) next.push_back(c);
        }
        std::cout << "\n";
        level = next;
    }
    return 0;
}
