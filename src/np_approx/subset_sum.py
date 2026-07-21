# 子集和 FPTAS（改寫自官方 Chapter 35/subset_sum.py，MIT License）
# EXACT：可能和的清單逐項合併（指數）；APPROX：每輪 TRIM 修剪相近值 → (1+ε) 保證
def exact_subset_sum(S, t):
    L = [0]
    for x in S:
        L = sorted(set(L + [v + x for v in L]))     # L ⊕ x 後合併
        L = [v for v in L if v <= t]
    return max(L)


def trim(L, delta):
    out = [L[0]]
    last = L[0]
    for v in L[1:]:
        if v > last * (1 + delta):          # 與代表值差超過 δ 才保留
            out.append(v)
            last = v
    return out


def approx_subset_sum(S, t, eps):
    n = len(S)
    L = [0]
    for x in S:
        L = sorted(set(L + [v + x for v in L]))
        L = trim(L, eps / (2 * n))          # 每輪修剪：total 誤差 ≤ (1+ε)
        L = [v for v in L if v <= t]
        print("處理", x, "後 L =", L)
    return max(L)


S, t, eps = [104, 102, 201, 101], 308, 0.40     # CLRS §35.5 的例子
print("exact  =", exact_subset_sum(S, t))
z = approx_subset_sum(S, t, eps)
print("approx =", z, "（比值 %.4f ≤ 1+ε = 1.4）" % (exact_subset_sum(S, t) / z))
