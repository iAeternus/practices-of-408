//! 二叉树 顺序存储 0-based
#include <bits/stdc++.h>

constexpr int N = 1e3 + 5;
int tree[N];
int size;

int fa(int i) {
    return (i - 1) / 2;
}

int lch(int i) {
    return 2 * i + 1;
}

int rch(int i) {
    return 2 * i + 2;
}

void preorder(int rt) {
    if (rt < 0 || rt >= size) return;
    std::cout << tree[rt] << ' ';
    preorder(lch(rt));
    preorder(rch(rt));
}

void inorder(int rt) {
    if (rt < 0 || rt >= size) return;
    inorder(lch(rt));
    std::cout << tree[rt] << ' ';
    inorder(rch(rt));
}

void postorder(int rt) {
    if (rt < 0 || rt >= size) return;
    postorder(lch(rt));
    postorder(rch(rt));
    std::cout << tree[rt] << ' ';
}

int main() {
    for (int i = 0; i < 10; ++i) {
        tree[i] = i;
    }
    size = 10;

    /*
    0 1 3 7 8 4 9 2 5 6
    7 3 8 1 9 4 0 5 2 6
    7 8 3 9 4 1 5 6 2 0
    */
    preorder(0);
    std::cout << std::endl;
    inorder(0);
    std::cout << std::endl;
    postorder(0);
    std::cout << std::endl;

    for (int i = 0; i < size; ++i) {
        std::cout << tree[i] << ' ';
    }
    std::cout << std::endl;
}