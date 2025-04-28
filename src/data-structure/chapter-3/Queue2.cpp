/**
 * 两个栈模拟一个队列
 * @see 84-03
 */
#include <bits/stdc++.h>

struct Queue {
    std::stack<int> st1;
    std::stack<int> st2;

    void enqueue(int x) {
        // 注意：如果是题目给的栈，需要在这里判断st1是否满，若满则将st1中所有元素出栈并压入st2中
        st1.push(x);
    }

    void dequeue(int& x) {
        if(st2.empty()) {
            while(!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        x = st2.top();
        st2.pop();
    }

    bool empty() const {
        return st1.empty() && st2.empty();
    }
};

auto it_works = []() {
    Queue q;
    assert(q.empty());

    q.enqueue(1), q.enqueue(2), q.enqueue(3);
    assert(!q.empty());
    
    int x;
    q.dequeue(x);
    assert(x == 1);
    q.dequeue(x);
    assert(x == 2);
    q.dequeue(x);
    assert(x == 3);

    assert(q.empty());
};

int main() {
    it_works();
}