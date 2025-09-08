/**
 * 对称阵压缩存储
 */
#include <cassert>
#include <iostream>

constexpr int n = 5;
int a[n][n] = {
    {1, 2, 3, 4, 5},
    {2, 6, 7, 8, 9},
    {3, 7, 8, 7, 6},
    {4, 8, 7, 5, 4},
    {5, 9, 6, 4, 3},
};
int a_row_first[] = {1, 2, 6, 3, 7, 8, 4, 8, 7, 5, 5, 9, 6, 4, 3};
int a_col_first[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3};

int row_first_1_based(int i, int j) {
    if (i >= j) {
        return i * (i - 1) / 2 + j - 1;
    } else {
        return j * (j - 1) / 2 + i - 1;
    }
}

void test_row_first_1_based() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            assert(a_row_first[row_first_1_based(i, j)] == a_row_first[row_first_1_based(j, i)]);
        }
    }
}

int row_first_0_based(int i, int j) {
    if (i >= j) {
        return (i + 1) * i / 2 + j;
    } else {
        return (j + 1) * j / 2 + i;
    }
}

void test_row_first_0_based() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(a_row_first[row_first_0_based(i, j)] == a_row_first[row_first_0_based(j, i)]);
        }
    }
}

// ------------------------------------------------

int col_first_1_based(int i, int j) {
    if (i >= j) {
        return (2 * n - j + 2) * (j - 1) / 2 + i - j;
    } else {
        return (2 * n - i + 2) * (i - 1) / 2 + j - i;
    }
}

void test_col_first_1_based() {
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            assert(a_col_first[col_first_1_based(i, j)] == a_col_first[col_first_1_based(j, i)]);
        }
    }
}

int col_first_0_based(int i, int j) {
    if (i >= j) {
        return (2 * n - j + 1) * j / 2 + i - j;
    } else {
        return (2 * n - i + 1) * i / 2 + j - i;
    }
}

void test_col_first_0_based() {
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            assert(a_col_first[col_first_0_based(i, j)] == a_col_first[col_first_0_based(j, i)]);
        }
    }
}

int main() {
    test_row_first_1_based();
    test_row_first_0_based();
    test_col_first_1_based();
    test_col_first_0_based();
    std::cout << "All tests passed!\n";
    return 0;
}