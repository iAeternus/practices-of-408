//! 循环队列 线性存储 牺牲一个单元来区分队空和队满
#include <bits/stdc++.h>

constexpr int N = 10;
int arr[N];
int begin = 0, end = 0; // 队列范围：[begin, end)

bool empty() {
    return begin == end;
}

bool full() {
    return (end + 1) % N == begin;
}

void push(int x) {
    if(full()) {
        return;
    }
    arr[end % N] = x;
    end = (end + 1) % N;
}

void pop() {
    if(empty()) {
        return;
    }
    begin = (begin + 1) % N;
}

int front() {
    return arr[begin];
}

int rear() {
    return arr[((end - 1) % N + N) % N];
}

int size() {
    return (end - begin + N) % N;
}

int main() {
    int n = 9;
    for (int i = 1; i <= n; ++i) {
        push(i);
    }
    assert(full());
    assert(size() == 9); 
    assert(front() == 1);
    assert(rear() == 9);
    pop();
    assert(!full());
    assert(size() == 8);
    assert(front() == 2);

    push(10); 
    assert(size() == 9); 
    assert(front() == 2);
    assert(rear() == 10);
    std::cout << "All tests passed!\n";
}