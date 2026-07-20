# 改寫自官方 Chapter 8/counting_sort.py（MIT License）：值域 0..k
def counting_sort(A, k):
    C = [0] * (k + 1)
    for a in A:                     # ① 計數：C[v] = 值 v 的個數
        C[a] += 1
    for v in range(1, k + 1):       # ② 前綴和：C[v] = 「≤ v 的個數」
        C[v] += C[v - 1]
    B = [None] * len(A)
    for a in reversed(A):           # ③ 從後往前放 → 相等元素保持原順序（穩定）
        B[C[a] - 1] = a
        C[a] -= 1
    return B


A = [6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2]
print(counting_sort(A, 6))
