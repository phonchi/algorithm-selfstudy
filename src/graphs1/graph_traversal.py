# BFS＋DFS 時間戳＋拓撲排序（改寫自官方 Chapter 20/bfs.py、dfs.py、topological_sort.py，
# MIT License）：dict 鄰接表平鋪版
from collections import deque


def bfs(adj, s):
    d = {v: None for v in adj}              # None = WHITE（未發現）
    d[s] = 0
    Q = deque([s])
    while Q:
        u = Q.popleft()
        for v in adj[u]:
            if d[v] is None:                # 白 → 灰：設距離、入列
                d[v] = d[u] + 1
                Q.append(v)
    return d


def dfs(adj):
    disc, fin = {}, {}
    time = [0]

    def visit(u):
        time[0] += 1
        disc[u] = time[0]                   # 發現（塗灰）
        for v in adj[u]:
            if v not in disc:
                visit(v)
        time[0] += 1
        fin[u] = time[0]                    # 完成（塗黑）

    for u in adj:                           # 主迴圈按插入順序選白色起點
        if u not in disc:
            visit(u)
    return disc, fin


# CLRS 圖 20.3（無向，r s t u v w x y）
G = {"r": ["s", "v"], "s": ["r", "w"], "t": ["u", "w", "x"], "u": ["t", "x", "y"],
     "v": ["r"], "w": ["s", "t", "x"], "x": ["t", "u", "w", "y"], "y": ["u", "x"]}
d = bfs(G, "s")
print("BFS 距離（源點 s）：", " ".join("%s:%d" % (v, d[v]) for v in sorted(d)))

# CLRS 圖 20.7 穿衣 DAG
H = {"內褲": ["褲子", "鞋"], "褲子": ["皮帶", "鞋"], "皮帶": ["外套"],
     "襯衫": ["皮帶", "領帶"], "領帶": ["外套"], "外套": [],
     "襪子": ["鞋"], "鞋": [], "錶": []}
disc, fin = dfs(H)
topo = sorted(H, key=lambda v: -fin[v])     # 完成時間反序 = 拓撲序
print("topological sort：", " ".join(topo))
