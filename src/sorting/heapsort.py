# 改寫自官方 Chapter 6/heap.py＋heapsort.py（MIT License）：攤平成三個函式（0-based）
def max_heapify(A, heap_size, i):
    l, r = 2 * i + 1, 2 * i + 2
    largest = i
    if l < heap_size and A[l] > A[largest]:
        largest = l
    if r < heap_size and A[r] > A[largest]:
        largest = r
    if largest != i:
        A[i], A[largest] = A[largest], A[i]
        max_heapify(A, heap_size, largest)      # 被換下去的值繼續下沉


def build_max_heap(A):
    for i in range(len(A) // 2 - 1, -1, -1):    # 最後內部節點倒著往前
        max_heapify(A, len(A), i)


def heapsort(A):
    build_max_heap(A)
    for i in range(len(A) - 1, 0, -1):
        A[0], A[i] = A[i], A[0]                 # 堆頂（最大）歸位到尾端
        max_heapify(A, i, 0)                    # heap 縮成 i 格後修復堆頂


A = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]
B = A[:]
build_max_heap(B)
print("build_max_heap:", B)
heapsort(A)
print("heapsort:", A)
