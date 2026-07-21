# 0/1 背包（自寫；官方 clrsPython 未附）：填表＋回溯選了哪些物品
def knapsack(w, v, W):
    n = len(w)
    dp = [[0] * (W + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for c in range(W + 1):
            dp[i][c] = dp[i - 1][c]                 # 不拿第 i 件
            if c >= w[i - 1]:
                dp[i][c] = max(dp[i][c],
                               dp[i - 1][c - w[i - 1]] + v[i - 1])   # 拿
    chosen, c = [], W
    for i in range(n, 0, -1):                        # 回溯：值變了 ⟺ 有拿
        if dp[i][c] != dp[i - 1][c]:
            chosen.append(i)
            c -= w[i - 1]
    return dp, sorted(chosen)


w, v, W = [2, 3, 4, 5], [3, 4, 5, 8], 9
dp, chosen = knapsack(w, v, W)
print("最大價值 =", dp[len(w)][W], "，選物品：", chosen)
for i in range(len(w) + 1):                          # 全表（trace 用）
    print("i=%d：%s" % (i, dp[i]))
