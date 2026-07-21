# 改寫自官方 Chapter 19/disjoint_set_forest.py（MIT License）：parent/rank dict 平鋪版
parent = {}
rank = {}


def make_set(x):
    parent[x] = x
    rank[x] = 0


def find_set(x):
    if parent[x] != x:
        parent[x] = find_set(parent[x])     # 路徑壓縮：沿途全改指根
    return parent[x]


def union(x, y):
    rx, ry = find_set(x), find_set(y)
    if rx == ry:
        return
    if rank[rx] < rank[ry]:                 # union by rank：矮樹掛高樹
        rx, ry = ry, rx
    parent[ry] = rx
    if rank[rx] == rank[ry]:
        rank[rx] += 1


for c in "abcdefghij":
    make_set(c)
for x, y in [("b", "c"), ("a", "c"), ("a", "b"), ("d", "c"),
             ("e", "f"), ("g", "h"), ("i", "j")]:       # CLRS 圖 19.1 的邊
    union(x, y)
print("SAME-COMPONENT(a, d) =", find_set("a") == find_set("d"))
print("SAME-COMPONENT(e, g) =", find_set("e") == find_set("g"))
print("各頂點代表：", {c: find_set(c) for c in "abcdefghij"})
