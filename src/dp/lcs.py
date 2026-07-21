# 改寫自官方 Chapter 14/longest_common_subsequence.py（MIT License）：含重建全文
def lcs_length(X, Y):
    m, n = len(X), len(Y)
    c = [[0] * (n + 1) for _ in range(m + 1)]
    b = [[""] * (n + 1) for _ in range(m + 1)]      # 方向表：↖ ↑ ←
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if X[i - 1] == Y[j - 1]:
                c[i][j] = c[i - 1][j - 1] + 1
                b[i][j] = "↖"                       # 配對成功
            elif c[i - 1][j] >= c[i][j - 1]:
                c[i][j] = c[i - 1][j]
                b[i][j] = "↑"
            else:
                c[i][j] = c[i][j - 1]
                b[i][j] = "←"
    return c, b


def print_lcs(b, X, i, j):                          # 沿 ↖ 反向收字
    if i == 0 or j == 0:
        return ""
    if b[i][j] == "↖":
        return print_lcs(b, X, i - 1, j - 1) + X[i - 1]
    if b[i][j] == "↑":
        return print_lcs(b, X, i - 1, j)
    return print_lcs(b, X, i, j - 1)


X, Y = "ABCBDAB", "BDCABA"
c, b = lcs_length(X, Y)
print("LCS 長度 =", c[len(X)][len(Y)])
print("LCS =", print_lcs(b, X, len(X), len(Y)))
