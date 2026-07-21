# B-tree（改寫自官方 Chapter 18/b_tree.py 精簡，MIT License）：t = 2、split 上浮
T = 2                                        # 最小分支度：鍵數 t-1 ~ 2t-1


class BNode:
    def __init__(self, leaf=True):
        self.keys = []
        self.ch = []
        self.leaf = leaf


def split_child(x, i):
    y = x.ch[i]
    z = BNode(y.leaf)
    mid = y.keys[T - 1]                      # 中位鍵上浮
    z.keys = y.keys[T:]
    y.keys = y.keys[:T - 1]
    if not y.leaf:
        z.ch = y.ch[T:]
        y.ch = y.ch[:T]
    x.keys.insert(i, mid)
    x.ch.insert(i + 1, z)
    print("split：%s 上浮" % mid)


def insert_nonfull(x, k):
    if x.leaf:
        x.keys.append(k)
        x.keys.sort()
    else:
        i = len(x.keys)
        while i > 0 and k < x.keys[i - 1]:
            i -= 1
        if len(x.ch[i].keys) == 2 * T - 1:   # 路過全滿節點先分裂
            split_child(x, i)
            if k > x.keys[i]:
                i += 1
        insert_nonfull(x.ch[i], k)


def insert(root, k):
    if len(root.keys) == 2 * T - 1:          # 根滿：長高一層（唯一長高方式）
        s = BNode(leaf=False)
        s.ch.append(root)
        split_child(s, 0)
        insert_nonfull(s, k)
        return s
    insert_nonfull(root, k)
    return root


root = BNode()
for k in "FSQKCLHTVWMRN":
    root = insert(root, k)
level, d = [root], 0
while level:
    print("第 %d 層：%s" % (d, " ".join("[" + " ".join(x.keys) + "]" for x in level)))
    level = [c for x in level for c in x.ch]
    d += 1
