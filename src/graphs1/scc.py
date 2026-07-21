# 強連通元件（改寫自官方 Chapter 20/strongly_connected_components.py，MIT License）
# 兩趟 DFS：G 記完成順序 → G 轉置 → 按完成時間遞減收割
G = {"a": ["b"], "b": ["c", "e", "f"], "c": ["d", "g"], "d": ["c", "h"],
     "e": ["a", "f"], "f": ["g"], "g": ["f", "h"], "h": ["h"]}   # CLRS 圖 20.9

order = []                                  # 第一趟：完成順序
visited = set()


def dfs1(u):
    visited.add(u)
    for v in G[u]:
        if v not in visited:
            dfs1(v)
    order.append(u)                         # 完成時 push → order 尾端 f 最大


for u in G:
    if u not in visited:
        dfs1(u)

GT = {u: [] for u in G}                     # 轉置圖：所有邊反向
for u in G:
    for v in G[u]:
        GT[v].append(u)

comp = {}                                   # 第二趟：在 G^T 上按 f 遞減收割


def dfs2(u, c):
    comp[u] = c
    for v in GT[u]:
        if v not in comp:
            dfs2(v, c)


sccs = []
for u in reversed(order):                   # f 最大者優先當起點
    if u not in comp:
        c = len(sccs)
        dfs2(u, c)
        sccs.append([v for v in comp if comp[v] == c])
print("共 %d 個 SCC：" % len(sccs))
for s in sccs:
    print("  {", " ".join(sorted(s)), "}")
