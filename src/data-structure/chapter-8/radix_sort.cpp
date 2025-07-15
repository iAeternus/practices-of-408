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
        free(temp);
    }
}

int max_val(Node* head) {
    int max_val = head->val;
    for (Node* p = head->next; p; p = p->next) {
        if (p->val > max_val) {
            max_val = p->val;
        }
    }
    return max_val;
}

int max_val(int arr[], int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; ++i) {
        max_val = std::max(max_val, arr[i]);
    }
    return max_val;
}

int digit_count(int x) {
    int cnt = 0;
    while (x) {
        ++cnt;
        x /= 10;
    }
    return cnt;
}

int qpow(int a, int x) {
    int res = 1;
    while (x) {
        if (x & 1) res *= a;
        a *= a;
        x >>= 1;
    }
    return res;
}

/**
 * @brief 基数排序
 * @note 时间复杂度：d趟分配和收集，分配的时间复杂度为O(n)，一趟收集需要合并r个队列，时间复杂度为O(r)，总时间复杂度为O(d(n + r))
 * @note 空间复杂度：O(r)
 * @note 稳定性：稳定
 * @note 适用于顺序存储和链式存储的线性表
 */
void radix_sort(Node** head_ptr) {
    if (!*head_ptr) return;

    Node *heads[10], *tails[10];
    int d = digit_count(max_val(*head_ptr));
    for (int exp = 0; exp < d; ++exp) {
        // 初始化桶
        for (int i = 0; i < 10; ++i) {
            heads[i] = tails[i] = nullptr;
        }
        // 分配节点到桶中
        Node* curr = *head_ptr;
        int base = qpow(10, exp);
        while (curr) {
            Node* next = curr->next;
            int digit = (curr->val / base) % 10;
            curr->next = nullptr;
            if (!heads[digit]) {
                heads[digit] = tails[digit] = curr;
            } else {
                tails[digit]->next = curr;
                tails[digit] = curr;
            }
            curr = next;
        }
        // 收集桶中的节点
        *head_ptr = nullptr;
        Node* last = nullptr;
        for (int i = 0; i < 10; ++i) {
            if (heads[i]) {
                if (!*head_ptr) {
                    *head_ptr = heads[i];
                    last = tails[i];
                } else {
                    last->next = heads[i];
                    last = tails[i];
                }
            }
        }
    }
}

void test_list() {
    Node* head = make_node(49, make_node(38, make_node(65, make_node(97, make_node(76, make_node(13, make_node(27, make_node(49, nullptr))))))));

    radix_sort(&head);

    for (Node* p = head; p; p = p->next) {
        std::cout << p->val << ' ';
    }
    std::cout << std::endl;

    free_list(head);
}

// 基数排序，顺序存储
void radix_sort(int arr[], int n) {
    int d = digit_count(max_val(arr, n));
    int tmp[10], cnt[10];
    for (int exp = 0; exp < d; ++exp) {
        std::memset(cnt, 0, sizeof(cnt));
        int base = qpow(10, exp);
        // 分配
        for (int i = 0; i < n; ++i) {
            ++cnt[(arr[i] / base) % 10];
        }
        // 收集
        for (int i = 1; i < 10; ++i) {
            cnt[i] += cnt[i - 1]; // 求前缀和后cnt[i]表示小于等于数位i的元素个数
        }
        for (int i = n - 1; i >= 0; --i) {
            tmp[--cnt[(arr[i] / base) % 10]] = arr[i];
        }
        std::memcpy(arr, tmp, sizeof(int) * n);
    }
}

void test_array() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {
    test_list();
    test_array();
}