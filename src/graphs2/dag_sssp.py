# DAG 最短路徑（CLRS §22.2，改寫自官方 dag_shortest_paths.py，MIT License）
# 拓撲排序後「按序單趟鬆弛」——允許負權、Θ(V+E)、比 Dijkstra 還快
INF = float("inf")
adj = {"r": [("s",5),("t",3)], "s": [("t",2),("x",6)],
       "t": [("x",7),("y",4),("z",2)],
       "x": [("y",-1),("z",1)], "y": [("z",-2)], "z": []}   # CLRS 圖 22.5


def topological_sort(adj):
    fin, visited = [], set()

    def visit(u):
        visited.add(u)
        for v, _ in adj[u]:
            if v not in visited:
                visit(v)
        fin.append(u)

    for u in adj:
        if u not in visited:
            visit(u)
    return list(reversed(fin))              # 完成時間反序


def dag_shortest_paths(adj, s):
    d = {v: INF for v in adj}
    d[s] = 0
    for u in topological_sort(adj):          # 按拓撲序
        if d[u] == INF:
            continue
        for v, w in adj[u]:                  # 每條邊恰鬆弛一次
            if d[u] + w < d[v]:
                d[v] = d[u] + w
    return d


d = dag_shortest_paths(adj, "s")
print("DAG-SHORTEST-PATHS（源點 s）：",
      " ".join("%s:%s" % (v, "∞" if d[v] == INF else d[v]) for v in "rstxyz"))
