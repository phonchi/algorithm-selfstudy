# OS-tree（改寫自官方 Chapter 17/order_statistic_tree.py 精簡，MIT License）：
# BST＋size 欄位 → OS-SELECT / OS-RANK（示範版未平衡；課本掛紅黑樹）
class Node:
    def __init__(self, key):
        self.key = key
        self.size = 1
        self.l = self.r = self.p = None


def sz(x):
    return x.size if x else 0


def insert(root, k):
    z = Node(k)
    x, y = root, None
    while x is not None:
        x.size += 1                          # 沿路每個祖先 size + 1
        y = x
        x = x.l if k < x.key else x.r
    z.p = y
    if y is None:
        return z
    if k < y.key:
        y.l = z
    else:
        y.r = z
    return root


def os_select(x, i):                          # 第 i 小
    r = sz(x.l) + 1                           # x 在自己子樹中的名次
    if i == r:
        return x
    return os_select(x.l, i) if i < r else os_select(x.r, i - r)


def os_rank(root, x):                         # x 的整體名次
    r = sz(x.l) + 1
    y = x
    while y is not root:
        if y is y.p.r:                        # 右孩子：加左兄弟子樹＋父
            r += sz(y.p.l) + 1
        y = y.p
    return r


root = None
for k in [26,17,41,14,21,30,47,10,16,19,20,28,38,7,12,3,35,39]:
    root = insert(root, k)
print("OS-SELECT(root, 10) =", os_select(root, 10).key)
x = root
while x.key != 38:
    x = x.l if 38 < x.key else x.r
print("OS-RANK(38) =", os_rank(root, x))
