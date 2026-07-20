# hiring problem 模擬：RANDOMLY-PERMUTE（Fisher–Yates，同官方 Ch5 版）＋雇用計數
import random

random.seed(42)                             # 固定 seed 讓輸出可重現


def randomly_permute(A, n):
    for i in range(n):
        j = random.randint(i, n - 1)        # 從 A[i..n-1] 均勻挑一個和 A[i] 交換
        A[i], A[j] = A[j], A[i]


def hire_count(n):
    A = list(range(1, n + 1))               # rank 1..n
    randomly_permute(A, n)
    best = hires = 0
    for r in A:
        if r > best:                        # 比目前最佳好 → 換人（雇用）
            best, hires = r, hires + 1
    return hires


n, trials = 100, 20000
avg = sum(hire_count(n) for _ in range(trials)) / trials
H = sum(1 / i for i in range(1, n + 1))
print("模擬平均雇用次數 = %.4f（理論值 H_100 = %.4f）" % (avg, H))
