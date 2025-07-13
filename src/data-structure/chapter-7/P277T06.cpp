#include <cassert>

bool two_d_search(int mat[][3], int n, int target) {
    int i = 0, j = n - 1;
    while (i < n && j >= 0) {
        if (mat[i][j] == target) {
            return true;
        } else if (mat[i][j] > target) {
            --j;
        } else {
            ++i;
        }
    }
    return false;
}

int main() {
    int mat[][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9},
    };
    assert(two_d_search(mat, 3, 8) == true);
}