/*
sample input
5 7
1 2
1 4
2 3
2 4
3 5
4 3
4 5

sample output
1 2 4 3 5
*/
#include <bits/stdc++.h>

constexpr int N = 1e5 + 3;
std::vector<int> adj[N], ans;
int n, m, d[N]; // 顶点数 边数 入度数组

/**
 * @brief 拓扑排序，bfs实现
 * @note 时间复杂度 O(|V| + |E|)
 */
auto topological_sort_bfs() -> bool {
    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (d[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        ans.push_back(u);
        for (int i = 0; i < adj[u].size(); ++i) {
            auto v = adj[u][i];
            d[v]--;
            if (d[v] == 0) {
                q.push(v);
            }
        }
    }

    return ans.size() == n; // 若拓扑序长度小于顶点数，拓扑排序失败，说明图中有回路
}

auto main() -> int {
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        d[v]++;
        adj[u].push_back(v);
    }

    if (topological_sort_bfs()) {
        for (const auto& it : ans) {
            std::cout << it + 1 << ' ';
        }
    } else {
        std::cout << "topological sort failed\n";
    }
}