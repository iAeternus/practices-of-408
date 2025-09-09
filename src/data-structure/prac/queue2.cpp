//! 队列 无头结点单链表 头插尾删
#include <bits/stdc++.h>

struct Node {
    int val;
    Node* next;
};

bool empty(const Node* head) {
    return head == nullptr;
}

void push(Node** head, int x) {
    Node* node = new Node;
    node->val = x;
    node->next = nullptr;
    if (empty(*head)) {
        *head = node;
        return;
    }
    node->next = *head;
    *head = node;
}

void pop(Node** head) {
    if (empty(*head)) {
        return;
    }
    Node* p = *head;
    while (p->next->next) {
        p = p->next;
    }
    Node* d = p->next;
    p->next = nullptr;
    delete d;
}

void clear(Node** head) {
    Node* p = *head;
    while (p) {
        *head = p->next;
        delete p;
        p = *head;
    }
}

int front(Node* head) {
    Node* p = head;
    while (p && p->next) {
        p = p->next;
    }
    return p->val;
}

int rear(Node* head) {
    return head->val;
}

int main() {
    int n = 10;
    Node* head = nullptr;
    for (int i = 1; i <= n; ++i) {
        push(&head, i);
    }
    assert(front(head) == 1);
    assert(rear(head) == 10);
    pop(&head);
    assert(front(head) == 2);

    push(&head, 11);
    assert(front(head) == 2);
    assert(rear(head) == 11);

    clear(&head);
    assert(empty(head));
}