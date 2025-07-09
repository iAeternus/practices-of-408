/*
sample input
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
1

sample output
0 8 9 7 5
*/
#include <bits/stdc++.h>

constexpr int N = 1e5 + 3;
constexpr int INF = 1e9 + 7;

std::vector<std::pair<int, int>> adj[N];
int n, m;

auto dijkstra(int s) -> std::vector<int> {
    std::vector<int> dis(n, INF);
    dis[s] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); // d 距离 u 点
        pq.pop();
        if (d > dis[u]) continue;
        dis[u] = d;
        for (const auto& [v, w] : adj[u]) {
            int nd = dis[u] + w;
            if (nd < dis[v]) {
                dis[v] = nd;
                pq.emplace(nd, v);
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

    int s;
    std::cin >> s;
    s--;
    auto dis = dijkstra(s);

    for (const auto& it : dis) {
        std::cout << it << ' ';
    }
}