# 改寫自官方 Chapter 15/activity_selector.py（MIT License）：遞迴＋迭代兩版
s = [0, 1, 3, 0, 5, 3, 5, 6, 7, 8, 2, 12]      # CLRS 圖 15.1（索引 0 為哨兵）
f = [0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16]  # 已按結束時間排序


def recursive_activity_selector(s, f, k, n):
    m = k + 1
    while m <= n and s[m] < f[k]:      # 找第一個與 a_k 相容的活動
        m += 1
    if m <= n:
        return [m] + recursive_activity_selector(s, f, m, n)
    return []


def greedy_activity_selector(s, f, n):
    A = [1]                            # a1 必選（最早結束）
    k = 1
    for m in range(2, n + 1):
        if s[m] >= f[k]:               # 與上一個選中的活動相容
            A.append(m)
            k = m
    return A


n = len(s) - 1
print("遞迴版：", recursive_activity_selector(s, f, 0, n))
print("迭代版：", greedy_activity_selector(s, f, n))
