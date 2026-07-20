# 改寫自官方 Chapter 2/insertion_sort.py（MIT License）：0-based
def insertion_sort(A, n):
    for i in range(1, n):
        key = A[i]
        # 將 A[i] 插入已排序的 A[0:i]
        j = i - 1
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = key


A = [5, 2, 4, 6, 1, 3]
insertion_sort(A, len(A))
print(A)
