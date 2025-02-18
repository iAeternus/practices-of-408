#include <bits/stdc++.h>

struct Node {
    int freq = 0;
    int data;
    Node *prev, *next;

    Node(int data = 0, Node* prev = nullptr, Node* next = nullptr) :
            data(data), prev(prev), next(next) {}
};

struct Chain {
    Node* head;
    int size;

    // 默认构造函数
    Chain() :
            size(0) {
        head = new Node();
    }

    // 简便起见，这里构造出的链表的倒序的
    Chain(std::initializer_list<int> initial_list) :
            size(0) {
        head = new Node();
        for (int value : initial_list) {
            push_front(value);
        }
    }

    ~Chain() {
        clear();
        delete head;
    }

    // 在链表头部插入元素
    void push_front(int value) {
        Node* newNode = new Node(value, head, head->next);
        if (head->next) {
            head->next->prev = newNode;
        }
        head->next = newNode;
        size++;
    }

    // 从链表头部移除元素
    void pop_front() {
        if (isEmpty()) {
            return;
        }
        Node* temp = head->next;
        head->next = temp->next;
        if (temp->next) {
            temp->next->prev = head;
        }
        delete temp;
        size--;
    }

    // 清空链表
    void clear() {
        while (!isEmpty()) {
            pop_front();
        }
    }

    // 打印链表
    void print() const {
        Node* current = head->next;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // 检查链表是否为空
    bool isEmpty() const {
        return head->next == nullptr;
    }

    //////////////////////////////////// PAGE 43 ////////////////////////////////////

    /**
     * @see 43-13
     */
    void locate(int x) {
        // 遍历链表找到x
        Node* p = head->next;
        while (p) {
            if (p->data == x) {
                break;
            }
            p = p->next;
        }
        if (!p) {
            return;
        }

        p->freq++;

        // 删除p指向的节点，但不释放内存
        p->prev->next = p->next;
        if (p->next) {
            p->next->prev = p->prev;
        }

        // 从表头开始寻找插入p指向节点的位置
        Node* q = head->next;
        while (q && q->freq > p->freq) {
            q = q->next;
        }

        // 插入在q的前面
        p->next = q;
        p->prev = q->prev;
        q->prev->next = p;
        q->prev = p;
    }
};

auto it_works = []() {
    Chain c = {1, 2, 3, 4, 5};
    c.print();

    c.push_front(0);
    c.print();

    c.pop_front();
    c.print();

    c.clear();
    c.print();

    return 0;
};

auto should_locate = []() {
    Chain c = {10, 20, 30, 40}; // 40 30 20 10
    c.locate(30);
    c.print();

    c.locate(30);
    c.print();

    c.locate(10);
    c.print();

    c.locate(10);
    c.locate(10);
    c.print();

    c.locate(50);
    c.print();
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    it_works();
    separator();

    should_locate();
    separator();
}