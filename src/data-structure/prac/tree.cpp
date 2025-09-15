//! 树 父亲表示法
//! 根节点的父节点下标为 -1
//! 若有多个节点的父节点下标为 -1 则表示的是森林
#include <bits/stdc++.h>

constexpr int N = 100;

struct Node {
    char val; // 节点值
    int fa;   // 父节点下标
};

struct Tree {
    Node nodes[N];
    int n; // 节点数
};

int main() {
    Tree t;
    t.nodes[0] = {'R', -1};
    t.nodes[1] = {'A', 0};
    t.nodes[2] = {'B', 0};
    t.nodes[3] = {'C', 0};
    t.nodes[4] = {'D', 1};
    t.nodes[5] = {'E', 1};
    t.nodes[6] = {'F', 3};
    t.nodes[7] = {'G', 6};
    t.nodes[8] = {'H', 6};
    t.nodes[9] = {'I', 6};
    t.n = 10;
}