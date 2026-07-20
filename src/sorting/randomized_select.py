# 改寫自官方 Chapter 9/randomized_select.py（MIT License）：含 partition 全文
import random

random.seed(42)


def partition(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]
    return i + 1


def randomized_partition(A, p, r):
    i = random.randint(p, r)
    A[i], A[r] = A[r], A[i]
    return partition(A, p, r)


def randomized_select(A, p, r, i):
    if p == r:
        return A[p]
    q = randomized_partition(A, p, r)
    k = q - p + 1                       # pivot 在本段排第 k 小
    if i == k:
        return A[q]
    if i < k:
        return randomized_select(A, p, q - 1, i)
    return randomized_select(A, q + 1, r, i - k)   # 進右半段要扣掉左邊 k 個


A = [3, 2, 9, 0, 7, 5, 4, 8, 6, 1]
for i in (1, 5, 10):
    print("第", i, "小 =", randomized_select(A[:], 0, len(A) - 1, i))
