//! 图 邻接表
#include <bits/stdc++.h>

using NV = int;
using EV = int;
using Idx = int;
using Target = Idx;

struct Node {
    Target target;
    Node* next;
};

struct AdjacencyList {
    Node* head;
    int size;
};

struct Graph {
    std::vector<AdjacencyList> lists;
    int edge_count;
};

int main() {
}