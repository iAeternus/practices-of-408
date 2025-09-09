//! 栈 无头结点双链表
#include <bits/stdc++.h>

struct Node {
    int val;
    Node* prev;
    Node* next;
};

bool empty(const Node* head) {
    return head == nullptr;
}

void push(Node** head, int x) {
    Node* node = new Node;
    node->val = x;
    node->next = node->prev = nullptr;
    if (empty(*head)) {
        *head = node;
        return;
    }

    Node* p = *head;
    while (p && p->next) {
        p = p->next;
    }
    node->prev = p;
    p->next = node;
}

void pop(Node** head) {
    if (empty(*head)) {
        return;
    }
    Node* p = *head;
    while (p && p->next) {
        p = p->next;
    }
    p->prev->next = nullptr;
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

int top(Node* head) {
    Node* p = head;
    while (p && p->next) {
        p = p->next;
    }
    return p->val;
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
}