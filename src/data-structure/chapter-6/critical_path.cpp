/*
sample input 1
7 8
0 1 3
0 2 2
1 3 2
1 4 3
2 4 4
3 5 3
4 5 1
5 6 4

sample output 1
Event times (ve and vl):
Node 0: ve = 0, vl = -1
Node 1: ve = 3, vl = 2
Node 2: ve = 2, vl = 2 (Critical Event)
Node 3: ve = 5, vl = 4
Node 4: ve = 6, vl = 6 (Critical Event)
Node 5: ve = 7, vl = 7 (Critical Event)
Node 6: ve = 11, vl = 11 (Critical Event)

Activity times:
Activity 0 (0->1): e = 0, l = -1, d = -1
Activity 1 (0->2): e = 0, l = 0, d = 0 (Critical Activity)
Activity 2 (1->3): e = 3, l = 2, d = -1
Activity 3 (1->4): e = 3, l = 3, d = 0 (Critical Activity)
Activity 4 (2->4): e = 2, l = 2, d = 0 (Critical Activity)
Activity 5 (3->5): e = 5, l = 4, d = -1
Activity 6 (4->5): e = 6, l = 6, d = 0 (Critical Activity)
Activity 7 (5->6): e = 7, l = 7, d = 0 (Critical Activity)

sample input 2
6 8
0 1 3
0 2 2
1 3 2
1 4 3
2 3 4
2 5 3
3 5 2
4 5 1

sample output 2
Event times (ve and vl):
Node 0: ve = 0, vl = 0 (Critical Event)
Node 1: ve = 3, vl = 4
Node 2: ve = 2, vl = 2 (Critical Event)
Node 3: ve = 6, vl = 6 (Critical Event)
Node 4: ve = 6, vl = 7
Node 5: ve = 8, vl = 8 (Critical Event)

Activity times:
Activity 0 (0->1): e = 0, l = 1, d = 1
Activity 1 (0->2): e = 0, l = 0, d = 0 (Critical Activity)
Activity 2 (1->3): e = 3, l = 4, d = 1
Activity 3 (1->4): e = 3, l = 4, d = 1
Activity 4 (2->3): e = 2, l = 2, d = 0 (Critical Activity)
Activity 5 (2->5): e = 2, l = 5, d = 3
Activity 6 (3->5): e = 6, l = 6, d = 0 (Critical Activity)
Activity 7 (4->5): e = 6, l = 7, d = 1

sample input 3
6 8
0 1 3
0 2 8
1 3 9
1 4 6
2 1 4
2 4 10
3 5 6
4 5 9

sample output 3
Event times (ve and vl):
Node 0: ve = 0, vl = 0 (Critical Event)
Node 1: ve = 12, vl = 12 (Critical Event)
Node 2: ve = 8, vl = 8 (Critical Event)
Node 3: ve = 21, vl = 21 (Critical Event)
Node 4: ve = 18, vl = 18 (Critical Event)
Node 5: ve = 27, vl = 27 (Critical Event)

Activity times:
Activity 0 (0->1): e = 0, l = 9, d = 9
Activity 1 (0->2): e = 0, l = 0, d = 0 (Critical Activity)
Activity 2 (1->3): e = 12, l = 12, d = 0 (Critical Activity)
Activity 3 (1->4): e = 12, l = 12, d = 0 (Critical Activity)
Activity 4 (2->1): e = 8, l = 8, d = 0 (Critical Activity)
Activity 5 (2->4): e = 8, l = 8, d = 0 (Critical Activity)
Activity 6 (3->5): e = 21, l = 21, d = 0 (Critical Activity)
Activity 7 (4->5): e = 18, l = 18, d = 0 (Critical Activity)
*/
#include <bits/stdc++.h>

constexpr int N = 1e5 + 3;

std::vector<std::pair<int, int>> adj[N]; // 邻接表：节点->{邻居, 权重}
int n, m;                                // 节点数、边数
int ve[N], vl[N];                        // 事件最早/最晚发生时间
int e[N], l[N], d[N];                    // 活动最早/最晚开始时间及余量
std::vector<int> topo;                   // 拓扑序列

auto topological_sort() -> bool {
    std::vector<int> in_deg(n);
    std::queue<int> q;

    for (int u = 0; u < n; ++u) {
        for (const auto& [v, w] : adj[u]) {
            in_deg[v]++;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (in_deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        topo.push_back(u);
        for (const auto& [v, w] : adj[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) {
                q.push(v);
                ve[v] = std::max(ve[v], ve[u] + w); // 更新最早发生时间
            }
        }
    }

    return topo.size() == n;
}

auto calc_vl() -> void {
    int total_time = *std::max_element(ve, ve + n); // 总工期
    std::fill(vl, vl + n, total_time);

    // 逆拓扑序更新 vl
    for (int i = topo.size() - 1; i >= 0; --i) {
        int u = topo[i];
        for (const auto& [v, w] : adj[u]) {
            vl[u] = std::min(vl[u], vl[v] - w); // 用后继节点的vl更新当前节点
        }
    }
}

auto calc_d() -> void {
    int idx = 0;
    for (int u = 0; u < n; ++u) {
        for (const auto& [v, w] : adj[u]) {
            e[idx] = ve[u];           // 最早开始时间
            l[idx] = vl[v] - w;       // 最晚开始时间
            d[idx] = l[idx] - e[idx]; // 时间余量
            ++idx;
        }
    }
}

auto critical_path() -> void {
    if (!topological_sort()) {
        throw std::runtime_error("Error: Graph contains cycle!");
    }

    calc_vl();
    calc_d();
}

auto print_results() -> void {
    std::cout << "Event times (ve and vl):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Node " << i << ": ve = " << ve[i] << ", vl = " << vl[i];
        // 标记关键事件（ve == vl）
        if (ve[i] == vl[i]) {
            std::cout << " (Critical Event)";
        }
        std::cout << "\n";
    }

    std::cout << "\nActivity times:\n";
    int idx = 0; // 活动索引
    // 遍历所有节点
    for (int u = 0; u < n; ++u) {
        // 遍历节点的所有出边
        for (const auto& [v, w] : adj[u]) {
            std::cout << "Activity " << idx << " ("
                      << u << "->" << v << "): "
                      << "e = " << e[idx] << ", l = " << l[idx]
                      << ", d = " << d[idx];
            // 标记关键活动（d == 0）
            if (d[idx] == 0) {
                std::cout << " (Critical Activity)";
            }
            std::cout << "\n";
            idx++;
        }
    }
}

auto main() -> int {
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    critical_path();
    print_results();
}