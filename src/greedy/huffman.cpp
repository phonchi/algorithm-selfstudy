// huffman.cpp — CLRS 4e §15.3：min-priority queue 反覆合併頻率最小兩節點
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Node {
    char ch; long long freq;
    Node *left = nullptr, *right = nullptr;
};

struct Cmp {   // 頻率小的優先；同頻率按字元序讓結果確定
    bool operator()(const Node* a, const Node* b) const {
        if (a->freq != b->freq) return a->freq > b->freq;
        return a->ch > b->ch;
    }
};

void printCodes(const Node* x, std::string code) {
    if (!x->left && !x->right) {
        std::cout << x->ch << ": " << code << '\n';
        return;
    }
    printCodes(x->left, code + "0");
    printCodes(x->right, code + "1");
}

int main() {
    // CLRS 圖 15.5 的頻率表（千次）
    std::vector<std::pair<char, long long>> freq =
        {{'a',45},{'b',13},{'c',12},{'d',16},{'e',9},{'f',5}};
    std::priority_queue<Node*, std::vector<Node*>, Cmp> Q;
    for (auto [c, f] : freq) Q.push(new Node{c, f});
    while (Q.size() > 1) {                       // n−1 次合併
        Node* x = Q.top(); Q.pop();
        Node* y = Q.top(); Q.pop();
        Q.push(new Node{'*', x->freq + y->freq, x, y});
    }
    printCodes(Q.top(), "");
    return 0;
}
