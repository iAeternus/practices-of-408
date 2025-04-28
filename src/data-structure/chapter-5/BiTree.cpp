#include <bits/stdc++.h>

/**
 * @see 135-05
 * @brief 顺序存储二叉树最近公共祖先
 * 规定0为空节点
 */
int lca(const std::vector<int>& v, int i, int j) {
    if (v[i] == 0 || v[j] == 0) {
        return 0;
    }
    while (i != j) {
        if (i > j) {
            i >>= 1;
        } else {
            j >>= 1;
        }
    }
    return v[i];
}

auto should_calc_lca = []() {
    // Given
    std::vector<int> v = {0, 1, 2, 3, 0, 4, 0, 5, 0, 0, 6};
    int i = 10, j = 7; // 节点6和节点5

    // When
    int res = lca(v, i, j);

    // Then
    assert(res == 1);
};

int main() {
    should_calc_lca();
}