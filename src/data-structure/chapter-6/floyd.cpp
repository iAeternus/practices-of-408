/*
sample input 1
5 10
1 2 10
1 5 5
2 3 1
2 5 2
3 4 4
4 1 7
4 3 6
5 2 3
5 3 9
5 4 2

sample output 1
0 8 9 7 5
11 0 1 4 2
11 19 0 4 16
7 15 6 0 12
9 3 4 2 0

sample input 2
3 5
1 2 6
1 3 13
2 1 10
2 3 4
3 1 5

sample output 2
0 6 10 
9 0 4 
5 11 0 
*/
#include <bits/stdc++.h>

constexpr int N = 1e5 + 3;
constexpr int INF = 1e9 + 7;

std::vector<std::pair<int, int>> adj[N];
int n, m;

auto floyd() -> std::vector<std::vector<int>> {
    std::vector<std::vector<int>> dis(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        dis[i][i] = 0;
    }
    for (int u = 0; u < n; ++u) {
        for (const auto& [v, w] : adj[u]) {
            dis[u][v] = w;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int u = 0; u < n; ++u) {
            if (dis[u][k] == INF) continue;
            for (int v = 0; v < n; ++v) {
                dis[u][v] = std::min(dis[u][v], dis[u][k] + dis[k][v]);
            }
        }
    }

    return dis;
}

auto main() -> int {
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        adj[u].emplace_back(v, w);
    }

    auto res = floyd();

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            std::cout << res[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}