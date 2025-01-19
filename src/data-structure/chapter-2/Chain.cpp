#include <bits/stdc++.h>

using value_t = int;

/**
 * @brief 单链表，不带头结点
 */
struct Chain {
    struct Node {
        value_t data;
        Node* next;

        Node(const value_t& data, Node* next = nullptr) :
                data(data), next(next) {}
    };

    int length;
    Node* head;

    Chain() :
            length(0), head(nullptr) {}

    ~Chain() {
        clear();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node* at(int idx) const {
        if (idx < 0 || idx > length) {
            return nullptr;
        }
        Node* p = head;
        for (int i = 0; p && i < idx; ++i) {
            p = p->next;
        }
        return p;
    }

    Node* find(value_t target) const {
        for (Node* p = head; p; p = p->next) {
            if (p->data == target) {
                return p;
            }
        }
        return nullptr;
    }

    void clear() {
        Node* p = head;
        while (p) {
            Node* q = p;
            p = p->next;
            delete q;
        }
        length = 0;
    }

    bool insert(int idx, value_t elem) {
        if (idx < 0) return false;

        Node* newNode = new Node{elem};
        if (idx == 0) { // 头插
            newNode->next = head;
            head = newNode;
        } else {
            Node* p = head;
            for (int i = 0; p && i < idx - 1; i++) {
                p = p->next;
            }
            if (!p) {
                delete newNode;
                return false;
            }
            newNode->next = p->next;
            p->next = newNode;
        }
        length++;
        return true;
    }

    bool remove(int idx, value_t& elem) {
        if (idx < 0) return false;

        Node** p = &head; // 指向首元结点前驱的next，虚拟前驱
        for (int i = 0; i < idx; ++i) {
            if (!p || !(*p)) return false;
            p = &((*p)->next); // 最终p指向待删除节点的前驱的next指针
        }
        Node* q = *p; // 获取待删除节点
        if (!q) return false;

        elem = q->data;
        *p = q->next;
        delete q;
        length--;
        return true;
    }

    void print() const {
        for (Node* p = head; p; p = p->next) {
            std::cout << p->data << ' ';
        }
        std::cout << std::endl;
    }
};

auto should_operates = []() {
    Chain c;

    int n = 10;
    for (int i = 0; i < n; ++i) {
        c.insert(0, i);
    }
    c.print();

    int elem;
    c.remove(0, elem);
    c.print();
    std::cout << elem << std::endl;

    c.remove(5, elem);
    c.print();
    std::cout << elem << std::endl;
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    should_operates();
    separator();
}