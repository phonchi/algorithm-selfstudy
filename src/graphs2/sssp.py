# Bellman-Ford＋Dijkstra（改寫自官方 Chapter 22，MIT License）：平鋪版
import heapq

INF = float("inf")

# ---- Bellman-Ford：CLRS 圖 22.4（含負權）----
E = [("s","t",6),("s","y",7),("t","x",5),("t","y",8),("t","z",-4),
     ("x","t",-2),("y","x",-3),("y","z",9),("z","x",7),("z","s",2)]
d = {v: INF for v in "stxyz"}
d["s"] = 0
for _ in range(4):                          # |V| − 1 輪全邊鬆弛
    for u, v, w in E:
        if d[u] + w < d[v]:
            d[v] = d[u] + w                 # RELAX(u, v, w)
ok = all(d[u] + w >= d[v] for u, v, w in E)  # 第 |V| 輪：還能鬆 = 負環
print("Bellman-Ford 回傳", ok, "：", " ".join("%s:%d" % (v, d[v]) for v in "stxyz"))

# ---- Dijkstra：CLRS 圖 22.6（非負權），heapq lazy deletion ----
adj = {"s": [("t",10),("y",5)], "t": [("x",1),("y",2)], "x": [("z",4)],
       "y": [("t",3),("x",9),("z",2)], "z": [("s",7),("x",6)]}
dist = {v: INF for v in adj}
dist["s"] = 0
h = [(0, "s")]
while h:
    du, u = heapq.heappop(h)
    if du > dist[u]:                        # 過期項目跳過
        continue
    for v, w in adj[u]:
        if dist[u] + w < dist[v]:
            dist[v] = dist[u] + w
            heapq.heappush(h, (dist[v], v))
print("Dijkstra：", " ".join("%s:%d" % (v, dist[v]) for v in "stxyz"))
