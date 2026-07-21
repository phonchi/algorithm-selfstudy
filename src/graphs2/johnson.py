# Johnson 全點對最短路徑（改寫自官方 Chapter 23/johnson.py，MIT License）：
# 超級源點 Bellman-Ford 求 h → 重新加權 w'(u,v)=w+h(u)−h(v) ≥ 0 → 每點跑 Dijkstra
import heapq

INF = float("inf")
n = 5
E = [(0,1,3),(0,2,8),(0,4,-4),(1,3,1),(1,4,7),(2,1,4),(3,0,2),(3,2,-5),(4,3,6)]

# ① 超級源點 q 連到所有頂點（權 0），Bellman-Ford 求 h
h = [0] * (n + 1)                            # 頂點 n 當 q，h 初值即 d(q,·)=0 起跑
edges_q = E + [(n, v, 0) for v in range(n)]
for _ in range(n):
    for u, v, w in edges_q:
        if h[u] + w < h[v]:
            h[v] = h[u] + w
assert all(h[u] + w >= h[v] for u, v, w in edges_q), "有負環"
print("h =", h[:n])

# ② 重新加權：w'(u,v) = w + h(u) − h(v) ≥ 0（路徑長守恆：差固定 h(u)−h(v)）
adj = {u: [] for u in range(n)}
for u, v, w in E:
    adj[u].append((v, w + h[u] - h[v]))

# ③ 每個源點跑一次 Dijkstra，再把距離「還原」回原權重
D = []
for src in range(n):
    dist = [INF] * n
    dist[src] = 0
    pq = [(0, src)]
    while pq:
        du, u = heapq.heappop(pq)
        if du > dist[u]:
            continue
        for v, w in adj[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(pq, (dist[v], v))
    D.append([dist[v] + h[v] - h[src] if dist[v] < INF else INF
              for v in range(n)])            # 還原：加回 h(v) − h(src)

print("D（與 Floyd-Warshall 相同）：")
for row in D:
    print("  ", row)
