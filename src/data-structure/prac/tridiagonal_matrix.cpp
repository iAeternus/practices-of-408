/**
 * 三对角矩阵压缩存储
 */
#include <cmath>
#include <cassert>
#include <iostream>

constexpr int n = 5;
int a[n][n] = {
    {1, 2, 0, 0, 0},
    {2, 2, 3, 0, 0},
    {0, 3, 3, 4, 0},
    {0, 0, 4, 4, 5},
    {0, 0, 0, 5, 5},
};
// 最后一个元素为非三对角区域的常量元素
int a_row_first[] = {1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 0};
int a_col_first[] = {1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 0};

int row_first(int i, int j) {
    if (abs(i - j) < 2) {
        return 2 * i + j - 3;
    } else {
        return 3 * n - 2;
    }
}

void test_row_first() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            assert(a_row_first[row_first(i, j)] == a_row_first[row_first(j, i)]);
        }
    }
}

int col_first(int i, int j) {
    if (abs(i - j) < 2) {
        return 2 * j + i - 3;
    } else {
        return 3 * n - 2;
    }
}

void test_col_first() {
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            assert(a_col_first[col_first(i, j)] == a_col_first[col_first(j, i)]);
        }
    }
}

int main() {
    test_row_first();
    test_col_first();
    std::cout << "All tests passed!\n";
    return 0;
}