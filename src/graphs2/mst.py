# Kruskal＋Prim（改寫自官方 Chapter 21/mst.py，MIT License）：平鋪版，CLRS 圖 21.4
import heapq

V = "abcdefghi"
E = [("a","b",4),("a","h",8),("b","h",11),("b","c",8),("c","i",2),("c","f",4),
     ("c","d",7),("d","f",14),("d","e",9),("e","f",10),("f","g",2),("g","i",6),
     ("g","h",1),("h","i",7)]

# ---- Kruskal：邊按權重排序＋union-find 擋環 ----
parent = {v: v for v in V}
rank = {v: 0 for v in V}


def find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]


def union(x, y):
    rx, ry = find(x), find(y)
    if rx == ry:
        return False
    if rank[rx] < rank[ry]:
        rx, ry = ry, rx
    parent[ry] = rx
    if rank[rx] == rank[ry]:
        rank[rx] += 1
    return True


total = 0
picked = []
for u, v, w in sorted(E, key=lambda e: e[2]):
    if union(u, v):                     # FIND 不同才收邊
        picked.append("%s-%s(%d)" % (u, v, w))
        total += w
print("Kruskal MST：", " ".join(picked), "｜總權重 =", total)

# ---- Prim：從 a 出發，heapq 挑 light edge（lazy deletion）----
adj = {v: [] for v in V}
for u, v, w in E:
    adj[u].append((w, v))
    adj[v].append((w, u))

in_mst, edges_out, total = set(), [], 0
h = [(0, "a", "")]                      # (key, 頂點, 來源)
while h:
    w, u, frm = heapq.heappop(h)
    if u in in_mst:                     # 過期項目跳過
        continue
    in_mst.add(u)
    total += w
    if frm:
        edges_out.append("%s-%s(%d)" % (frm, u, w))
    for wv, v in adj[u]:
        if v not in in_mst:
            heapq.heappush(h, (wv, v, u))
print("Prim MST：   ", " ".join(edges_out), "｜總權重 =", total)
