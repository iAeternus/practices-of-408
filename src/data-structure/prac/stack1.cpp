//! 栈 顺序存储
#include <bits/stdc++.h>

constexpr int N = 1e5 + 3;
int arr[N];
int siz = 0;

bool empty() {
    return siz == 0;
}

bool full() {
    return siz == N;
}

void push(int x) {
    arr[siz++] = x;
}

int top() {
    return arr[siz - 1];
}

void pop() {
    if(empty()) {
        return;
    }
    siz--;
}

int main() {
    int n = 10;
    assert(empty());
    for (int i = 1; i <= n; ++i) {
        push(i);
    }
    assert(top() == n);
    pop();
    assert(top() == n - 1);
}