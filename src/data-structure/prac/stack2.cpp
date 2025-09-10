//! 栈 无头结点单链表
#include <bits/stdc++.h>

struct Node {
    int val;
    Node* next;
};

int top(const Node* head) {
    return head->val;
}

bool empty(const Node* head) {
    return head == nullptr;
}

void push(Node** head, int x) {
    Node* node = new Node;
    node->val = x;
    node->next = *head;
    *head = node;
}

void pop(Node** head) {
    if(empty(*head)) {
        return;
    }
    Node* p = *head;
    *head = p->next;
    delete p;
}

void clear(Node** head) {
    Node* p = *head;
    while (p) {
        *head = p->next;
        delete p;
        p = *head;
    }
}

int main() {
    int n = 10;
    Node* head = nullptr;
    assert(empty(head));
    for (int i = 1; i <= n; ++i) {
        push(&head, i);
    }
    assert(top(head) == n);
    pop(&head);
    assert(top(head) == n - 1);

    clear(&head);
    assert(empty(head));
    std::cout << "All tests passed!\n";
}