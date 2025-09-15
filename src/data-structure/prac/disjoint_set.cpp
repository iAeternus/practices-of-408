/**
 * @see https://www.luogu.com.cn/problem/P3367
 */
#include <bits/stdc++.h>

constexpr int N = 2e5 + 3;
int n, m;
int fa[N], rk[N];

void init(int siz) {
    std::fill(rk, rk + siz, 0);
    for (int i = 0; i < siz; ++i) {
        fa[i] = i;
    }
}

/**
 * @brief 查询x的组长
 */
int find(int x) {
    while (x != fa[x]) {
        x = fa[x] = fa[fa[x]];
    }
    return x;
}

/**
 * @brief 合并x和y为一组
 * @return true=合并成功 false=合并失败，x和y已在同一组内
 */
bool merge(int x, int y) {
    auto fx = find(x), fy = find(y);
    if (fx == fy) return false;

    if (rk[fx] > rk[fy]) {
        fa[fy] = fx;
    } else {
        fa[fx] = fy;
        if (rk[fx] == rk[fy]) {
            ++rk[fy];
        }
    }
    return true;
}

/**
 * @brief 查询x和y是否在一组
 */
bool is_same(int x, int y) {
    return find(x) == find(y);
}

/*
4 7
2 1 2
1 1 2
2 1 2
1 3 4
2 1 4
1 2 3
2 1 4

N
Y
N
Y
*/
int main() {
    std::cin >> n >> m;
    init(n);
    while (m--) {
        int z, x, y;
        std::cin >> z >> x >> y;
        if (z == 1) {
            merge(x, y);
        } else {
            std::cout << (is_same(x, y) ? 'Y' : 'N') << '\n';
        }
    }
}