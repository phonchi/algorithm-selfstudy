# metric TSP 2-近似（改寫自官方 Chapter 35/approx_tsp_tour.py，MIT License）：
# Prim MST ＋ 前序走訪（子節點按編號序，與 C++ 版一致）
from math import dist

P = [(1,4),(1,2),(0,1),(3,4),(4,3),(3,2),(5,2),(2,0)]   # CLRS 圖 35.2 的 8 城
n = len(P)
names = "abcdefgh"

# Prim（根 = a）
parent = [-1] * n
key = [float("inf")] * n
key[0] = 0
used = [False] * n
for _ in range(n):
    u = min((v for v in range(n) if not used[v]), key=lambda v: key[v])
    used[u] = True
    for v in range(n):
        if not used[v] and dist(P[u], P[v]) < key[v]:
            key[v] = dist(P[u], P[v])
            parent[v] = u

children = [[] for _ in range(n)]
for v in range(1, n):
    children[parent[v]].append(v)           # 子節點天然按編號序

tour = []


def preorder(u):
    tour.append(u)
    for c in children[u]:
        preorder(c)


preorder(0)
cost = sum(dist(P[tour[i]], P[tour[(i + 1) % n]]) for i in range(n))
print("前序導覽：", "→".join(names[v] for v in tour) + "→a")
print("近似導覽成本 = %.3f（暴力最佳 14.715，比值 %.2f ≤ 2）" % (cost, cost / 14.7148))
