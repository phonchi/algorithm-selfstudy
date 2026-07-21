# 攤還分析兩個經典（改寫自官方 Chapter 16/increment.py＋multipop.py，MIT License）
def increment(A):
    """k 位元二進位計數器 +1，回傳本次翻轉的位元數。"""
    i = 0
    flips = 0
    while i < len(A) and A[i] == 1:     # 低位連續的 1 清成 0
        A[i] = 0
        i += 1
        flips += 1
    if i < len(A):                      # 第一個 0 設成 1
        A[i] = 1
        flips += 1
    return flips


A = [0] * 6
total = 0
for n in range(1, 17):
    total += increment(A)
print("16 次 INCREMENT 總翻轉 = %d（< 2n = 32），平均 %.2f" % (total, total / 16))


def multipop(S, k):                     # 彈出 min(k, |S|) 個
    cost = 0
    while S and k > 0:
        S.pop()
        k -= 1
        cost += 1
    return cost


S, cost = [], 0
ops = [("push", 1), ("push", 2), ("push", 3), ("push", 4), ("push", 5),
       ("multipop", 3), ("push", 6), ("push", 7), ("multipop", 4)]
for op, arg in ops:
    if op == "push":
        S.append(arg)
        cost += 1
    else:
        cost += multipop(S, arg)
print("9 個操作（7 push＋2 multipop）總成本 = %d ≤ 2×push 數 = 14" % cost)
