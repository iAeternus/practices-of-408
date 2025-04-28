#include <bits/stdc++.h>

const int MAX_SIZE = 5;

struct SharedStack {
    int data[MAX_SIZE];
    int top1 = -1;       // 左边的栈
    int top2 = MAX_SIZE; // 右边的栈

    bool isFull() const {
        return top2 - top1 == 1;
    }

    bool isEmpty1() const {
        return top1 == -1;
    }

    bool isEmpty2() const {
        return top2 == MAX_SIZE;
    }

    void push1(int elem) {
        if (isFull()) {
            return;
        }
        data[++top1] = elem;
    }

    void push2(int elem) {
        if (isFull()) {
            return;
        }
        data[--top2] = elem;
    }

    int pop1() {
        if(isEmpty1()) {
            return INT_MAX;
        }
        return data[top1--];
    }

    int pop2() {
        if(isEmpty2()) {
            return INT_MAX;
        }
        return data[top2++];
    }
};

auto it_works = []() {
    SharedStack st;
    assert(st.isEmpty1());
    assert(st.isEmpty2());

    st.push1(1), st.push1(2), st.push1(3);
    st.push2(1), st.push2(2);
    assert(st.isFull());

    assert(st.pop1() == 3);
    assert(st.pop1() == 2);
    assert(st.pop1() == 1);
    
    assert(st.pop2() == 2);
    assert(st.pop2() == 1);
};

int main() {
    it_works();
}