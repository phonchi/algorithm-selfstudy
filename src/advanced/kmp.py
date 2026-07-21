# KMP（改寫自官方 Chapter 32/kmp_matcher.py，MIT License）：1-based π 表版
def prefix_function(P):
    m = len(P)
    pi = [0] * (m + 1)                       # pi[q] = P[:q] 的最長真前綴兼後綴長
    k = 0
    for q in range(2, m + 1):
        while k > 0 and P[k] != P[q - 1]:
            k = pi[k]
        if P[k] == P[q - 1]:
            k += 1
        pi[q] = k
    return pi


def kmp_matcher(T, P):
    pi = prefix_function(P)
    q = 0                                    # 已匹配的字元數
    hits = []
    for i, ch in enumerate(T):
        while q > 0 and P[q] != ch:          # 失配：q 退到 π[q]，i 不回頭
            q = pi[q]
        if P[q] == ch:
            q += 1
        if q == len(P):
            hits.append(i - len(P) + 1)
            q = pi[q]
    return pi, hits


P = "ababaca"
pi, hits = kmp_matcher("abababacaba", P)
print("π 表（q=1..7）：")
for q in range(1, len(P) + 1):
    print("  q=%d  P[:q]=%-8s π[q]=%d" % (q, P[:q], pi[q]))
print("在 shift", hits, "找到 pattern")
