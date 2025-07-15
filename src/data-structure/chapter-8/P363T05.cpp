#include <bits/stdc++.h>

typedef struct _Node {
    int val;
    struct _Node* next;
} Node;

Node* make_node(int val, Node* next) {
    return new Node(val, next);
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void select_sort(Node* head) {
    for (Node* p = head; p; p = p->next) {
        Node* p_min = p;
        for (Node* q = p_min->next; q; q = q->next) {
            if (q->val < p_min->val) {
                p_min = q;
            }
        }
        if (p != p_min) {
            std::swap(p->val, p_min->val);
        }
    }
}

int main() {
    Node* head = make_node(49, make_node(38, make_node(65, make_node(97, make_node(76, make_node(13, make_node(27, make_node(49, NULL))))))));

    select_sort(head);

    for (Node* p = head; p; p = p->next) {
        std::cout << p->val << ' ';
    }
    std::cout << std::endl;

    free_list(head);
}