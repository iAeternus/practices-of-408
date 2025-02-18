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

    Chain(std::initializer_list<value_t>&& init_list) :
            length(init_list.size()) {
        Node* p = head;
        bool tag = true;
        for (auto&& ele : init_list) {
            Node* new_node = new Node(std::move(ele));
            if (tag) {
                head = new_node;
                p = new_node;
                tag = false;
            } else {
                p->next = new_node;
                p = p->next;
            }
        }
    }

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

    //////////////////////////////////// PAGE 43 ////////////////////////////////////

    /**
     * @see 43-14
     * 1. 找到尾节点，将尾节点指向头指针形成循环单链表；头指针指向原链表的n - k节点的next，断开链表即可
     * 3. 时间复杂度 O(n) 空间复杂复 O(1)
     */
    void rightShift(int k) {
        if (!head) return;

        // 找尾节点
        int n = 1;
        Node* p = head;
        while (p->next) {
            p = p->next;
            n++;
        }

        p->next = head; // 构造循环单链表
        for (int i = 0; i < n - k; ++i) {
            p = p->next;
        }
        head = p->next;
        p->next = nullptr;
    }

    /**
     * @see 43-16
     * 1. 使用快慢指针，快指针一次走两个节点，慢指针一次走一个节点，当快指针遍历到链表末尾时，慢指针指向链表中点
     * 反转慢指针到快指针的这一段链表，接着维护两个指针分别指向首元和慢指针，两指针指向的节点的值之和即为孪生和
     * 取最大即可
     * 3. 时间复杂度 O(n)，空间复杂度 O(1)
     */
    int maxTwinSum() {
        // 快慢指针找中点
        Node* s = head, *f = head->next;
        while(f && f->next) {
            f = f->next->next;
            s = s->next;
        }

        // 逆置链表后半部分
        Node* p = s->next, *r = nullptr;
        s->next = nullptr;
        while(p) {
            r = p->next;
            p->next = s->next;
            s->next = p;
            p = r;
        }

        // 计算孪生和
        Node* a = head, *b = s->next;
        int max_ans = 0;
        while(b) {
            max_ans = std::max(max_ans, a->data + b->data);
            a = a->next;
            b = b->next;
        }
        return max_ans;
    }
};

auto it_works = []() {
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

auto should_right_shift = []() {
    Chain c = {0, 1, 2, 3};
    c.rightShift(1);
    c.print(); // 3 0 1 2

    c.rightShift(2);
    c.print(); // 1 2 3 0
};

auto should_calc_max_twin_sum = []() {
    Chain c = {6, 2, 5, 1, 7, 2};
    assert(c.maxTwinSum() == 9);
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    it_works();
    separator();

    should_right_shift();
    separator();

    should_calc_max_twin_sum();
    separator();
}