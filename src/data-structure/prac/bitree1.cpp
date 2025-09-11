//! 二叉树 顺序存储 1-based
#include <bits/stdc++.h>

constexpr int N = 1e3 + 5;
int tree[N];
int size;

int fa(int i) {
    return i / 2;
}

int lch(int i) {
    return 2 * i;
}

int rch(int i) {
    return 2 * i + 1;
}

void preorder(int rt) {
    if (rt < 1 || rt >= size) return;
    std::cout << tree[rt] << ' ';
    preorder(lch(rt));
    preorder(rch(rt));
}

void inorder(int rt) {
    if (rt < 1 || rt >= size) return;
    inorder(lch(rt));
    std::cout << tree[rt] << ' ';
    inorder(rch(rt));
}

void postorder(int rt) {
    if (rt < 1 || rt >= size) return;
    postorder(lch(rt));
    postorder(rch(rt));
    std::cout << tree[rt] << ' ';
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        tree[i] = i;
    }
    size = 11;

    /*
    1 2 4 8 9 5 10 3 6 7 
    8 4 9 2 10 5 1 6 3 7 
    8 9 4 10 5 2 6 7 3 1 
    */
    preorder(1);
    std::cout << std::endl;
    inorder(1);
    std::cout << std::endl;
    postorder(1);
    std::cout << std::endl;

    for(int i = 0; i < size; ++i) {
        std::cout << tree[i] << ' ';
    }
    std::cout << std::endl;
}