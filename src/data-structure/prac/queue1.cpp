//! 循环队列 线性存储
#include <bits/stdc++.h>

constexpr int N = 10;
int arr[N];
int begin = 0, end = 0; // 队列范围：[begin, end)
int size = 0;

bool empty() {
    return size == 0;
}

bool full() {
    return size == N;
}

void push(int x) {
    if(full()) {
        return;
    }
    arr[end % N] = x;
    end = (end + 1) % N;
    ++size;
}

void pop() {
    if(empty()) {
        return;
    }
    begin = (begin + 1) % N;
    --size;
}

int front() {
    return arr[begin];
}

int rear() {
    return arr[((end - 1) % N + N) % N];
}

int main() {
    int n = 10;
    for(int i = 1; i <= n; ++i) {
        push(i);
    }
    assert(full());
    assert(front() == 1);
    assert(rear() == 10);
    pop();
    assert(!full());
    assert(front() == 2);

    push(11);
    assert(front() == 2);
    assert(rear() == 11);
}