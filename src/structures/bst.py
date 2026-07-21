# 改寫自官方 Chapter 12/binary_search_tree.py（MIT License）：Node＋平鋪函式
class Node:
    def __init__(self, key):
        self.key = key
        self.left = self.right = self.p = None


def tree_insert(T, z):
    x, y = T["root"], None
    while x is not None:                 # 追蹤落點
        y = x
        x = x.left if z.key < x.key else x.right
    z.p = y
    if y is None:
        T["root"] = z
    elif z.key < y.key:
        y.left = z
    else:
        y.right = z


def inorder(x, out):
    if x is not None:
        inorder(x.left, out)
        out.append(x.key)
        inorder(x.right, out)


def tree_minimum(x):
    while x.left is not None:
        x = x.left
    return x


def transplant(T, u, v):                 # 用子樹 v 整棵取代 u
    if u.p is None:
        T["root"] = v
    elif u is u.p.left:
        u.p.left = v
    else:
        u.p.right = v
    if v is not None:
        v.p = u.p


def tree_delete(T, z):
    if z.left is None:                   # 情境①：無左子 → 右子頂上
        transplant(T, z, z.right)
    elif z.right is None:                # 情境②：無右子 → 左子頂上
        transplant(T, z, z.left)
    else:                                # 情境③：兩子俱在 → 後繼接手
        y = tree_minimum(z.right)        # 後繼必無左子
        if y.p is not z:
            transplant(T, y, y.right)    # y 先脫離原位
            y.right = z.right
            y.right.p = y
        transplant(T, z, y)
        y.left = z.left
        y.left.p = y


def search(x, k):
    while x is not None and x.key != k:
        x = x.left if k < x.key else x.right
    return x


T = {"root": None}
for k in [12, 5, 18, 2, 9, 15, 19, 17]:
    tree_insert(T, Node(k))
out = []
inorder(T["root"], out)
print("inorder:", out)
tree_delete(T, search(T["root"], 12))    # 刪根（兩子俱在 → 後繼 15 接手）
out = []
inorder(T["root"], out)
print("刪 12 後:", out, "，新根 =", T["root"].key)
