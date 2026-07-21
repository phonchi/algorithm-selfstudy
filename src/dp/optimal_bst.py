# 改寫自官方 Chapter 14/optimal_BST.py（MIT License）：e/w/root 三表全文
def optimal_bst(p, q, n):
    # p[1..n]：命中機率；q[0..n]：落在間隙的機率（1-based 對齊課本）
    e = [[0.0] * (n + 1) for _ in range(n + 2)]     # e[i][j]，i 到 n+1
    w = [[0.0] * (n + 1) for _ in range(n + 2)]
    root = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 2):
        e[i][i - 1] = q[i - 1]                      # 空區間 = 只有間隙
        w[i][i - 1] = q[i - 1]
    for length in range(1, n + 1):                  # 區間長度由小到大
        for i in range(1, n - length + 2):
            j = i + length - 1
            e[i][j] = float("inf")
            w[i][j] = w[i][j - 1] + p[j] + q[j]
            for r in range(i, j + 1):               # 枚舉根
                t = e[i][r - 1] + e[r + 1][j] + w[i][j]
                if t < e[i][j]:
                    e[i][j] = t
                    root[i][j] = r
    return e, root


p = [0, 0.15, 0.10, 0.05, 0.10, 0.20]               # CLRS 圖 14.9
q = [0.05, 0.10, 0.05, 0.05, 0.05, 0.10]
e, root = optimal_bst(p, q, 5)
print("期望搜尋成本 e[1][5] = %.2f" % e[1][5])
print("整棵樹的根 root[1][5] = k%d" % root[1][5])
