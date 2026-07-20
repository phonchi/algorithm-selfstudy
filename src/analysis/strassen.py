# 改寫自官方 Chapter 4/matrix_multiply.py（MIT License）：純 list 的完整 Strassen
def mat_add(A, B, sign=1):
    return [[a + sign * b for a, b in zip(ra, rb)] for ra, rb in zip(A, B)]


def split(M):
    n = len(M) // 2
    return ([row[:n] for row in M[:n]], [row[n:] for row in M[:n]],
            [row[:n] for row in M[n:]], [row[n:] for row in M[n:]])


def strassen(A, B):
    n = len(A)
    if n == 1:                                   # 基底：1x1 直接乘
        return [[A[0][0] * B[0][0]]]
    A11, A12, A21, A22 = split(A)
    B11, B12, B21, B22 = split(B)
    P1 = strassen(A11, mat_add(B12, B22, -1))    # 7 次 n/2 規模的乘法
    P2 = strassen(mat_add(A11, A12), B22)
    P3 = strassen(mat_add(A21, A22), B11)
    P4 = strassen(A22, mat_add(B21, B11, -1))
    P5 = strassen(mat_add(A11, A22), mat_add(B11, B22))
    P6 = strassen(mat_add(A12, A22, -1), mat_add(B21, B22))
    P7 = strassen(mat_add(A11, A21, -1), mat_add(B11, B12))
    C11 = mat_add(mat_add(P5, P4), mat_add(P6, P2, -1))   # 加減法拼回四象限
    C12 = mat_add(P1, P2)
    C21 = mat_add(P3, P4)
    C22 = mat_add(mat_add(P5, P1), mat_add(P3, P7), -1)
    top = [r1 + r2 for r1, r2 in zip(C11, C12)]
    bot = [r1 + r2 for r1, r2 in zip(C21, C22)]
    return top + bot


A = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
B = [[17, 18, 19, 20], [21, 22, 23, 24], [25, 26, 27, 28], [29, 30, 31, 32]]
C = strassen(A, B)
naive = [[sum(A[i][k] * B[k][j] for k in range(4)) for j in range(4)]
         for i in range(4)]
print("Strassen 與傳統三重迴圈相符:", C == naive)
for row in C:
    print(row)
