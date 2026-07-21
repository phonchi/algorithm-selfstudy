# 改寫自官方 Chapter 14/matrix_chain_multiply.py（MIT License）：完整平鋪版
def matrix_chain_order(p):
    n = len(p) - 1                        # 矩陣個數
    m = [[0] * (n + 1) for _ in range(n + 1)]
    s = [[0] * (n + 1) for _ in range(n + 1)]
    for length in range(2, n + 1):        # 區間長度由小到大
        for i in range(1, n - length + 2):
            j = i + length - 1
            m[i][j] = float("inf")
            for k in range(i, j):         # 枚舉最後一次相乘的切點
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k
    return m, s


def print_optimal_parens(s, i, j):
    if i == j:
        return "A%d" % i
    return "(%s%s)" % (print_optimal_parens(s, i, s[i][j]),
                       print_optimal_parens(s, s[i][j] + 1, j))


p = [30, 35, 15, 5, 10, 20, 25]           # CLRS 圖 14.5 的例子
m, s = matrix_chain_order(p)
print("最少乘法次數 m[1][6] =", m[1][6])
print("最佳括號化：", print_optimal_parens(s, 1, 6))
