# Edmonds-Karp（改寫自官方 Chapter 24/ford_fulkerson.py，MIT License）：殘餘 dict 版
from collections import deque

names = ["s", "v1", "v2", "v3", "v4", "t"]
n, s, t = 6, 0, 5
cap = [[0] * n for _ in range(n)]            # 殘餘容量矩陣（含反悔邊）
for u, v, c in [(0,1,16),(0,2,13),(1,3,12),(2,1,4),(2,4,14),
                (3,2,9),(3,5,20),(4,3,7),(4,5,4)]:   # CLRS 圖 24.2 Lucky Puck
    cap[u][v] = c

max_flow = 0
while True:
    parent = [-1] * n                        # BFS 找殘餘網路的增廣路徑
    parent[s] = s
    Q = deque([s])
    while Q and parent[t] < 0:
        u = Q.popleft()
        for v in range(n):
            if parent[v] < 0 and cap[u][v] > 0:
                parent[v] = u
                Q.append(v)
    if parent[t] < 0:                        # 無增廣路徑 → 已達最大流
        break
    f = float("inf")                         # 路徑上的瓶頸
    v = t
    path = [t]
    while v != s:
        f = min(f, cap[parent[v]][v])
        v = parent[v]
        path.append(v)
    v = t
    while v != s:                            # 更新殘餘網路（含反悔邊）
        cap[parent[v]][v] -= f
        cap[v][parent[v]] += f
        v = parent[v]
    max_flow += f
    print("增廣路徑：%s，推 %d 單位" % ("→".join(names[x] for x in reversed(path)), f))
print("最大流 |f*| =", max_flow)
