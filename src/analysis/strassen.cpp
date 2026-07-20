// strassen.cpp — CLRS 4e §4.2（n 為 2 的冪；子矩陣以複製方式切割，重在演算法結構）
#include <iostream>
#include <vector>

using Mat = std::vector<std::vector<long long>>;

Mat add(const Mat& A, const Mat& B, long long sign = 1) {
    std::size_t n = A.size();
    Mat C(n, std::vector<long long>(n));
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < n; ++j)
            C[i][j] = A[i][j] + sign * B[i][j];
    return C;
}

Mat quadrant(const Mat& A, std::size_t r, std::size_t c, std::size_t h) {
    Mat Q(h, std::vector<long long>(h));
    for (std::size_t i = 0; i < h; ++i)
        for (std::size_t j = 0; j < h; ++j) Q[i][j] = A[r + i][c + j];
    return Q;
}

Mat strassen(const Mat& A, const Mat& B) {
    std::size_t n = A.size();
    if (n == 1) return {{A[0][0] * B[0][0]}};
    std::size_t h = n / 2;
    Mat A11 = quadrant(A, 0, 0, h), A12 = quadrant(A, 0, h, h),
        A21 = quadrant(A, h, 0, h), A22 = quadrant(A, h, h, h);
    Mat B11 = quadrant(B, 0, 0, h), B12 = quadrant(B, 0, h, h),
        B21 = quadrant(B, h, 0, h), B22 = quadrant(B, h, h, h);
    // 7 次遞迴乘法（取代直觀分治的 8 次）
    Mat P1 = strassen(A11, add(B12, B22, -1));
    Mat P2 = strassen(add(A11, A12), B22);
    Mat P3 = strassen(add(A21, A22), B11);
    Mat P4 = strassen(A22, add(B21, B11, -1));
    Mat P5 = strassen(add(A11, A22), add(B11, B22));
    Mat P6 = strassen(add(A12, A22, -1), add(B21, B22));
    Mat P7 = strassen(add(A11, A21, -1), add(B11, B12));
    Mat C11 = add(add(add(P5, P4), P6, 1), P2, -1);
    Mat C12 = add(P1, P2);
    Mat C21 = add(P3, P4);
    Mat C22 = add(add(P5, P1), add(P3, P7), -1);
    Mat C(n, std::vector<long long>(n));
    for (std::size_t i = 0; i < h; ++i)
        for (std::size_t j = 0; j < h; ++j) {
            C[i][j] = C11[i][j];         C[i][j + h] = C12[i][j];
            C[i + h][j] = C21[i][j];     C[i + h][j + h] = C22[i][j];
        }
    return C;
}

int main() {
    Mat A = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Mat B = {{17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32}};
    Mat C = strassen(A, B);
    // 對照傳統三重迴圈
    Mat D(4, std::vector<long long>(4, 0));
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            for (int j = 0; j < 4; ++j) D[i][j] += A[i][k] * B[k][j];
    std::cout << "Strassen 與傳統乘法相符: " << (C == D ? "true" : "false") << '\n';
    for (auto& row : C) {
        for (auto x : row) std::cout << x << ' ';
        std::cout << '\n';
    }
    return 0;
}
