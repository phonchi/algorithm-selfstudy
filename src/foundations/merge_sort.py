# 改寫自官方 Chapter 2/merge_sort.py（MIT License）：0-based、閉區間 [p, r]
def merge(A, p, q, r):
    nL = q - p + 1                          # A[p..q] 的長度
    nR = r - q                              # A[q+1..r] 的長度
    L = [A[p + i] for i in range(nL)]       # 複製左半
    R = [A[q + 1 + j] for j in range(nR)]   # 複製右半
    i = j = 0
    k = p
    while i < nL and j < nR:                # 兩疊都還有牌：取頂端較小者
        if L[i] <= R[j]:                    # 「≤」平手取左 → 穩定排序
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1
        k += 1
    while i < nL:                           # 左疊剩下的依序倒回
        A[k] = L[i]
        i += 1
        k += 1
    while j < nR:                           # 右疊剩下的依序倒回
        A[k] = R[j]
        j += 1
        k += 1


def merge_sort(A, p, r):
    if p >= r:                              # 0 或 1 個元素：已排序
        return
    q = (p + r) // 2
    merge_sort(A, p, q)                     # Divide + Conquer 左半
    merge_sort(A, q + 1, r)                 # Conquer 右半
    merge(A, p, q, r)                       # Combine


A = [12, 3, 7, 9, 14, 6, 11, 2]
merge_sort(A, 0, len(A) - 1)
print(A)
