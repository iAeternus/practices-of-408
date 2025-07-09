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
5 3 4 2 1
*/
#include <bits/stdc++.h>
#include <corecrt.h>

constexpr int N = 1e5 + 3;
std::vector<int> adj[N], ans;
int n, m; // 顶点数 边数

enum class Status {
    UNVISITED, // 未访问
    VISITING,  // 访问中
    VISITED,   // 已访问
};

/**
 * @brief 拓扑排序，bfs实现，计算逆拓扑序
 * @note 时间复杂度 O(|V| + |E|)
 */
auto topological_sort_dfs() -> bool {
    std::vector<Status> vis(n, Status::UNVISITED);

    std::function<bool(int)> dfs = [&](int u) {
        vis[u] = Status::VISITING;
        for (int v : adj[u]) {
            if (vis[v] == Status::UNVISITED) {
                if (dfs(v) == false) return false;
            } else if (vis[v] == Status::VISITING) {
                return false;
            }
        }

        vis[u] = Status::VISITED;
        ans.push_back(u);
        return true;
    };

    // 遍历所有未访问节点
    for (int i = 0; i < n; ++i) {
        if (vis[i] == Status::UNVISITED) {
            if (dfs(i) == false) return false;
        }
    }

    return true;
}

auto main() -> int {
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }

    if (topological_sort_dfs()) {
        for (const auto& it : ans) {
            std::cout << it + 1 << ' ';
        }
    } else {
        std::cout << "topological sort failed\n";
    }
}