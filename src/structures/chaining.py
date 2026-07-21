# 改寫自官方 Chapter 11/chained_hashtable.py（MIT License）：攤平成 list-of-list
def chained_insert(T, k):
    T[k % len(T)].insert(0, k)          # 插到鏈開頭：O(1)


def chained_search(T, k):
    slot = T[k % len(T)]
    for i, x in enumerate(slot):        # 沿鏈找：期望 Θ(1 + α)
        if x == k:
            return "slot %d 第 %d 格" % (k % len(T), i)
    return None


m = 9
T = [[] for _ in range(m)]
for k in [5, 28, 19, 15, 20, 33, 12, 17, 10]:
    chained_insert(T, k)
for s, slot in enumerate(T):
    print(s, "→", slot if slot else "∅")
n = sum(len(s) for s in T)
print("α = %d/%d = %.2f，最長鏈 = %d" % (n, m, n / m, max(len(s) for s in T)))
print("search(20):", chained_search(T, 20))
