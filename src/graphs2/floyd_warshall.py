# Floyd-Warshall（改寫自官方 Chapter 23/floyd_warshall.py，MIT License）：純 list 版
INF = float("inf")
W = [[0,   3,   8,   INF, -4],
     [INF, 0,   INF, 1,   7],
     [INF, 4,   0,   INF, INF],
     [2,   INF, -5,  0,   INF],
     [INF, INF, INF, 6,   0]]                # CLRS 圖 23.1

n = 5
d = [row[:] for row in W]
for k in range(n):                           # 中繼點只准用 {1..k}
    for i in range(n):
        for j in range(n):
            if d[i][k] + d[k][j] < d[i][j]:
                d[i][j] = d[i][k] + d[k][j]

print("D（所有點對最短路徑權重）：")
for row in d:
    print("  ", [int(x) for x in row])
