# 最壞情況線性 SELECT（CLRS §9.3 中位數之中位數；改寫自官方 order_statistics.py 精簡）
def select(A, i):
    """回傳 A 中第 i 小（1-based），最壞情況 O(n)。"""
    if len(A) <= 5:                       # 基底：小陣列直接排
        return sorted(A)[i - 1]
    # ① 5 個一組、各組取中位數
    medians = [sorted(A[j:j + 5])[len(A[j:j + 5]) // 2]
               for j in range(0, len(A), 5)]
    # ② 遞迴找「中位數們的中位數」當 pivot
    x = select(medians, (len(medians) + 1) // 2)
    # ③ 以 x 三路分割（保證兩側都至少甩掉約 3n/10 個元素）
    lo = [a for a in A if a < x]
    eq = [a for a in A if a == x]
    hi = [a for a in A if a > x]
    if i <= len(lo):
        return select(lo, i)
    if i <= len(lo) + len(eq):
        return x
    return select(hi, i - len(lo) - len(eq))


A = [3, 2, 9, 0, 7, 5, 4, 8, 6, 1, 12, 11, 10, 14, 13]
print("第 8 小（中位數）=", select(A, 8))
print("第 1 小 =", select(A, 1), "，第 15 小 =", select(A, 15))
