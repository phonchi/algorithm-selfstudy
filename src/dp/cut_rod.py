# 改寫自官方 Chapter 14/cut_rod.py（MIT License）：bottom-up＋memoized 兩版全文
p = [0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30]    # CLRS 圖 14.1 價目表（p[0] 不用）


def bottom_up_cut_rod(p, n):
    r = [0] * (n + 1)
    s = [0] * (n + 1)                     # s[j] = 長度 j 的最佳第一刀
    for j in range(1, n + 1):             # 子問題由小到大
        q = float("-inf")
        for i in range(1, j + 1):
            if p[i] + r[j - i] > q:
                q = p[i] + r[j - i]
                s[j] = i
        r[j] = q
    return r, s


def memoized_cut_rod(p, n, r=None):       # top-down：算過就查表
    if r is None:
        r = [None] * (n + 1)
    if r[n] is not None:
        return r[n]
    if n == 0:
        q = 0
    else:
        q = float("-inf")
        for i in range(1, n + 1):
            q = max(q, p[i] + memoized_cut_rod(p, n - i, r))
    r[n] = q
    return q


r, s = bottom_up_cut_rod(p, 10)
print("bottom-up r[10] =", r[10])
cuts, j = [], 10
while j > 0:                              # 由 s 表回溯切法
    cuts.append(s[j])
    j -= s[j]
print("切法：", cuts)
print("memoized r(10) =", memoized_cut_rod(p, 10))
print("r 表：", r)
