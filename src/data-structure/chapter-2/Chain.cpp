#include <bits/stdc++.h>

/**
 * @brief 单链表，带头结点
 */
template <typename T>
struct Chain {
    using value_t = T;

    struct Node {
        value_t data;
        Node* next;

        Node(const value_t& data = {}, Node* next = nullptr) :
                data(data), next(next) {}
    };

    int size;
    Node* head;

    Chain() :
            size(0), head(new Node{}) {}

    Chain(std::initializer_list<value_t>&& initList) :
            size(0), head(new Node{}) {
        for (auto&& elem : initList) {
            insert(size, elem);
        }
    }

    ~Chain() {
        clear();
        delete head; // 释放头结点
    }

    Node* at(int idx) const {
        if (idx < 0 || idx >= size) return nullptr;
        Node* current = head->next;
        for (int i = 0; i < idx; ++i) {
            current = current->next;
        }
        return current;
    }

    Node* find(const value_t& val) const {
        Node* current = head->next;
        while (current) {
            if (current->data == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool isEmpty() const {
        return head->next == nullptr;
    }

    void clear() {
        Node* current = head->next;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head->next = nullptr;
        size = 0;
    }

    bool insert(int idx, const value_t& val) {
        if (idx < 0 || idx > size) return false;
        Node* current = head;
        for (int i = 0; i < idx; ++i) {
            current = current->next;
        }
        current->next = new Node{val, current->next};
        ++size;
        return true;
    }

    bool remove(int idx, value_t& val) {
        if (idx < 0 || idx >= size) return false;
        Node* current = head;
        for (int i = 0; i < idx; ++i) {
            current = current->next;
        }
        Node* toDelete = current->next;
        val = toDelete->data;
        current->next = toDelete->next;
        delete toDelete;
        --size;
        return true;
    }

    void print() const {
        Node* current = head->next;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* back() {
        Node* p = head;
        while (p->next) {
            p = p->next;
        }
        return p;
    }

    //////////////////////////////////// PAGE 42 43 44 ////////////////////////////////////

    /**
     * @see 42-01
     */
    void removeAll(const value_t& val) {
        for (Node* p = head->next; p; p = p->next) {
            while (p->next && p->next->data == val) { // 连续删除
                Node* toDelete = p->next;
                p->next = toDelete->next;
                delete toDelete;
                --size;
            }
        }
    }

    /**
     * @see 42-02
     */
    void removeMin() {
        if (isEmpty()) return;
        Node* minPtr = head->next;
        value_t minVal = head->next->data;
        for (Node* p = head->next; p && p->next; p = p->next) {
            if (p->next->data < minVal) {
                minVal = p->next->data;
                minPtr = p;
            }
        }
        Node* toDelete = minPtr->next;
        minPtr->next = toDelete->next;
        delete toDelete;
        --size;
    }

    /**
     * @see 42-03
     * 摘下头结点，遍历链表，头插到头结点即可反转
     */
    void reverse() {
        Node *p = head->next, *r = nullptr;
        head->next = nullptr;
        while (p) {
            r = p->next;
            p->next = head->next;
            head->next = p;
            p = r;
        }
    }

    /**
     * 法二：遍历链表，指针反转
     */
    void reverse2() {
        Node *p = head->next, *r = p->next, *pre;
        p->next = nullptr;
        while (r) {
            pre = p;
            p = r;
            r = r->next;
            p->next = pre; // 指针反转
        }
        head->next = p;
    }

    /**
     * @see 42-04
     */
    void removeBetween(const T& min, const T& max) {
        Node *p = head, *r = p->next;
        while (r) {
            if (r->data >= min && r->data <= max) {
                p->next = r->next;
                delete r;
                --size;
                r = p->next;
            } else {
                p = r;
                r = r->next;
            }
        }
    }

    /**
     * @see 42-06
     */
    void split(Chain<T>& a, Chain<T>& b) {
        // TODO
    }

    /**
     * @see 43-07
     */
    void distinct() {
        for (Node* p = head->next; p && p->next; p = p->next) {
            while (p->data == p->next->data) {
                Node* q = p->next;
                p->next = q->next;
                delete q;
                size--;
            }
        }
    }

    /**
     * @see 43-08
     */
    void buildWithCommon(const Chain<T>& a, const Chain<T>& b) {
        clear();
        if (a.isEmpty() || b.isEmpty()) return;

        Node* r = head;
        Node *p = a.head->next, *q = b.head->next;
        while (p && q) {
            if (p->data > q->data) {
                q = q->next;
            } else if (p->data < q->data) {
                p = p->next;
            } else {
                r->next = new Node(p->data);
                r = r->next;
                ++size;
                p = p->next;
                q = q->next;
            }
        }
    }

    /**
     * @see 43-09
     */
    void intersection(const Chain<T>& b) {
        Node *p = head, *q = b.head;
        while (p->next && q->next) {
            if (p->next->data > q->next->data) {
                q = q->next;
            } else if (p->next->data < q->next->data) {
                // 删除p->next指向的节点，因为不在交集中
                Node* r = p->next;
                p->next = r->next;
                delete r;
                --size;
            } else {
                p = p->next;
                q = q->next;
            }
        }
    }

    /**
     * @see 43-10
     * TODO 可使用KMP优化
     */
    bool contains(const Chain<T>& b) const {
        Node *p = head->next, *q = b.head->next;
        Node* last = p;
        while (p && q) {
            if (p->data == q->data) {
                p = p->next;
                q = q->next;
            } else {
                last = last->next;
                p = last;
                q = b.head->next;
            }
        }
        return !q;
    }

    /**
     * @see 43-15
     * 1. 使用快慢指针，快指针一次走两个节点，慢指针一次走一个节点，如果链表有环，显然在某一时刻快慢指针会再次指向相同节点
     * 否则二者永远不会相遇
     * 3. 时间复杂度 O(n)，空间复杂度 O(1)
     */
    bool hasLoop() const {
        Node *f = head->next, *s = f;
        while (f && f->next) {
            s = s->next;
            f = f->next->next;
            if (s == f) {
                return true;
            }
        }
        return false;
    }

    /** 
     * @see 43-17
     * 1. 快慢指针均指向首元，快指针走到第k个节点时，慢指针与快指针同步移动，当快指针指向链表末尾，
     * 慢指针指向的节点即为所求节点
     * 3. 时间复杂度 O(n) 空间复杂度 O(1)
     */
    int findRev(int k) {
        Node *f = head->next, *s = f;
        for (int i = 0; f && i < k; ++i) {
            f = f->next;
        }
        if (!f) return 0;
        while (f) {
            s = s->next;
            f = f->next;
        }

        std::cout << s->data << std::endl;
        return 1;
    }

    /**
     * @see 44-19
     * 1. 空间换时间，使用哈希表存储已遍历过的值，对于当前值，查询其绝对值是否在哈希表中出现，
     * 若出现，则删除，否则继续遍历
     * 3. 时间复杂度 O(m)，空间复杂度 O(n)
     */
    void distinctAbs(int n) {
        bool* vis = new bool[n + 1];
        for (int i = 0; i < n + 1; ++i) {
            vis[i] = false;
        }
        for (Node* p = head; p && p->next; p = p->next) {
            if (!vis[abs(p->next->data)]) {     // 没出现过
                vis[abs(p->next->data)] = true; // 记录
                continue;
            }
            // 否则删除节点
            Node* q = p->next;
            p->next = q->next;
            delete q;
        }
        delete[] vis;
    }

    /**
     * @see 44-20
     * 1. 快慢指针均指向头结点，快指针一次走两个节点，慢指针一次走一个节点，当快指针走到链表末尾时，慢指针指向链表中点，
     * 接下来反转链表后半部分，从链表前半部分和后半部分各取一个节点，按要求重排
     */
    void cross() {
        // 快慢指针取中点
        Node *s = head, *f = head;
        while (f && f->next) {
            f = f->next->next;
            s = s->next;
        }

        // 反转链表后半部分
        Node *p = s->next, *r = nullptr;
        s->next = nullptr;
        while (p) {
            r = p->next;
            p->next = s->next;
            s->next = p;
            p = r;
        }

        // 排列
        Node *a = head->next, *b = s->next;
        s->next = nullptr; // 断开前后两半链表
        while (b) {
            r = b->next;
            b->next = a->next; // 将后半段指针指向的节点插入到前半段指针后
            a->next = b;
            a = b->next; // 前半段指针移动到下一个插入点
            b = r;       // 后半段指针后移
        }
    }
};

/**
 * @see 42-05
 */
template <typename T>
typename Chain<T>::Node* findCommon(const Chain<T>& c1, const Chain<T>& c2) {
    if (c1.isEmpty() || c2.isEmpty()) {
        return nullptr;
    }

    typename Chain<T>::Node* p = c1.head->next;
    typename Chain<T>::Node* q = c2.head->next;
    int size_diff = std::abs(c1.size - c2.size);
    if (c1.size > c2.size) {
        for (int i = 0; i < size_diff; ++i) {
            if (!p) return nullptr;
            p = p->next;
        }
    } else {
        for (int i = 0; i < size_diff; ++i) {
            if (!q) return nullptr;
            q = q->next;
        }
    }

    while (p && q) {
        if (p == q) {
            return p;
        }
        p = p->next;
        q = q->next;
    }

    return nullptr;
}

auto it_works = []() {
    Chain<int> c;

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

auto should_remove_all = []() {
    Chain<int> c = {1, 2, 2, 3, 2, 4, 5, 2};
    c.removeAll(2);
    c.print(); // 1 3 4 5
};

auto should_remove_min = []() {
    Chain<int> c = {5, 4, 3, 2, 1};
    c.removeMin();
    c.print();

    Chain<int> c2 = {5, 1, 4, 3, 2};
    c2.removeMin();
    c2.print();
};

auto should_reverse = []() {
    Chain<int> c = {1, 2, 3, 4, 5};
    c.reverse();
    c.print();

    c.reverse2();
    c.print();
};

auto should_remove_between = []() {
    Chain<int> c = {1, 2, 3, 4, 5};
    c.removeBetween(2, 4);
    c.print();

    c.removeBetween(0, 1);
    c.print();
};

auto should_find_common = []() {
    // 有公共节点
    Chain<int> c1 = {1, 2, 3};
    Chain<int> c2 = {4, 5, 6};
    auto* p = c1.back();
    auto* q = c2.back();
    Chain<int>::Node* common = new Chain<int>::Node(7, new Chain<int>::Node(8));
    p->next = common;
    q->next = common;
    c1.size += 2;
    c2.size += 2;

    auto* res = findCommon(c1, c2);
    assert(res == common); // 公共节点应为 7

    delete common->next;
    delete common;
    p->next = q->next = nullptr;
    c1.size -= 2;
    c2.size -= 2;

    // 无公共节点
    Chain<int> c3 = {1, 2, 3}, c4 = {4, 5, 6};
    res = findCommon(c3, c4);
    assert(res == nullptr); // 无公共节点

    // 链表为空
    Chain<int> c5, c6;
    res = findCommon(c5, c6);
    assert(res == nullptr); // 无公共节点

    // 一个链表为空
    Chain<int> c7 = {1, 2, 3};
    res = findCommon(c7, c6);
    assert(res == nullptr); // 无公共节点
};

auto should_distinct = []() {
    Chain<int> c = {7, 10, 10, 21, 30, 42, 42, 42, 51, 70};
    c.distinct();
    c.print(); // 7 10 21 30 42 51 70
};

auto should_build_with_common = []() {
    Chain<int> a = {1, 2, 3, 4, 5}, b = {3, 4, 5, 6, 7};
    Chain<int> c;
    c.buildWithCommon(a, b);
    c.print();
};

auto should_calc_intersection = []() {
    Chain<int> a = {1, 2, 3, 4, 5}, b = {3, 4, 5, 6, 7};
    a.intersection(b);
    a.print(); // 3 4 5
};

auto should_contains = []() {
    Chain<int> a = {1, 2, 3, 4, 5}, b = {2, 3, 4};
    assert(a.contains(b));
};

auto should_judge_loop = []() {
    Chain<int> c = {1, 2, 3, 4, 5};
    assert(c.hasLoop() == false);

    auto* p = c.back();
    typename Chain<int>::Node* q = c.head->next;
    for (int i = 0; i < 2; ++i) {
        q = q->next;
    }
    p->next = q;

    assert(c.hasLoop());

    p->next = nullptr;
};

auto should_find_rev = []() {
    Chain<int> c = {1, 2, 3, 4, 5, 6};
    assert(c.findRev(3) == 1); // 打印 4

    Chain<int> c2 = {1, 2};
    assert(c2.findRev(3) == 0); // 什么都不打印
};

auto should_distinct_abs = []() {
    Chain<int> c = {21, -15, -15, -7, 15};
    c.distinctAbs(21);
    c.print(); // 21 -15 -7
};

auto should_cross = []() {
    Chain<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    c.cross();
    c.print();
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    it_works();
    separator();

    should_remove_all();
    separator();

    should_remove_min();
    separator();

    should_reverse();
    separator();

    should_remove_between();
    separator();

    should_find_common();
    separator();

    should_distinct();
    separator();

    should_build_with_common();
    separator();

    should_calc_intersection();
    separator();

    should_contains();
    separator();

    should_judge_loop();
    separator();

    should_find_rev();
    separator();

    should_distinct_abs();
    separator();

    should_cross();
    separator();
}