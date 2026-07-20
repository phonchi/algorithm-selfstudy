# 改寫自官方 Chapter 7/randomized_quicksort.py（MIT License）：含 partition 全文
import random

random.seed(42)


def partition(A, p, r):
    x = A[r]                            # pivot 取最後一個元素
    i = p - 1                           # 「≤ x 區」的右邊界
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]     # pivot 歸位
    return i + 1


def randomized_partition(A, p, r):
    i = random.randint(p, r)            # 隨機挑 pivot 換到尾端
    A[i], A[r] = A[r], A[i]
    return partition(A, p, r)


def randomized_quicksort(A, p, r):
    if p < r:
        q = randomized_partition(A, p, r)
        randomized_quicksort(A, p, q - 1)   # pivot 已就定位，不再參與
        randomized_quicksort(A, q + 1, r)


A = [2, 8, 7, 1, 3, 5, 6, 4]
randomized_quicksort(A, 0, len(A) - 1)
print(A)
