# 最大優先佇列（CLRS §6.5；改寫自官方 max_heap_priority_queue.py，MIT License）
def max_heapify(A, heap_size, i):
    l, r = 2 * i + 1, 2 * i + 2
    largest = i
    if l < heap_size and A[l] > A[largest]:
        largest = l
    if r < heap_size and A[r] > A[largest]:
        largest = r
    if largest != i:
        A[i], A[largest] = A[largest], A[i]
        max_heapify(A, heap_size, largest)


def heap_maximum(A):                     # MAXIMUM：看堆頂，O(1)
    return A[0]


def heap_extract_max(A):                 # EXTRACT-MAX：尾端補頂、下沉修復，O(lg n)
    mx = A[0]
    A[0] = A[-1]
    A.pop()
    max_heapify(A, len(A), 0)
    return mx


def heap_increase_key(A, i, key):        # INCREASE-KEY：增鍵後往上浮，O(lg n)
    assert key >= A[i], "新 key 必須 >= 目前值"
    A[i] = key
    while i > 0 and A[(i - 1) // 2] < A[i]:   # 和父節點比，較大就浮上去
        A[i], A[(i - 1) // 2] = A[(i - 1) // 2], A[i]
        i = (i - 1) // 2


def max_heap_insert(A, key):             # INSERT：先塞 -inf 佔位，再增鍵上浮
    A.append(float("-inf"))
    heap_increase_key(A, len(A) - 1, key)


A = [16, 14, 10, 8, 7, 9, 3, 2, 4, 1]    # CLRS 圖 6.5 的 max-heap
max_heap_insert(A, 15)
print("INSERT(15) 後:", A)
print("EXTRACT-MAX =", heap_extract_max(A))
print("之後:", A)
