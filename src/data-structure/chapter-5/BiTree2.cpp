#include <bits/stdc++.h>

const int N = 1e3 + 5;

template <typename T>
struct Node {
    T data;
    Node<T>* lchild = nullptr;
    Node<T>* rchild = nullptr;

    Node(const T& data = {}, Node<T>* lchild = nullptr, Node<T>* rchild = nullptr) :
            data(data), lchild(lchild), rchild(rchild) {}
};

template <typename T>
struct BiTree {
    Node<T>* root = nullptr;

    ~BiTree() {
        clear();
    }

    void clear() {
        clear_subtree(root);
        root = nullptr;
    }

    static void clear_subtree(Node<T>* r) {
        if (!r) return;
        clear_subtree(r->lchild);
        clear_subtree(r->rchild);
        delete r;
    }

    /**
     * 152-03
     * 非递归，层序遍历数层数
     */
    int height() const {
        if (!root) return 0;

        int h = 0, last = 0;
        int front = -1, rear = -1;
        Node<T>* q[N];
        q[++rear] = root;
        while (front != rear) {
            Node<T>* node = q[++front];
            if (node->lchild) q[++rear] = node->lchild;
            if (node->rchild) q[++rear] = node->rchild;
            if (last == front) {
                ++h;
                last = rear;
            }
        }
        return h;
    }

    // 递归版
    int height_r() const {
        return height_r(root);
    }

    static int height_r(Node<T>* r) {
        if (!r) return 0;
        int lh = height_r(r->lchild);
        int rh = height_r(r->rchild);
        return std::max(lh, rh) + 1;
    }

    /**
     * 152-04
     * 层序遍历，只要遍历到空节点之后就不能再遇到非空节点，否则不是完全二叉树
     */
    bool is_complete() const {
        if (!root) return true;

        Node<T>* q[N];
        int front = -1, rear = -1;
        bool has_null = false;
        q[++rear] = root;
        while (front != rear) {
            Node<T>* p = q[++front];
            if (!p) {
                has_null = true;
            } else {
                if (has_null) return false;
                q[++rear] = p->lchild;
                q[++rear] = p->rchild;
            }
        }
        return true;
    }

    /**
     * 152-05
     */
    int branch_size() const {
        return branch_size(root);
    }

    static int branch_size(Node<T>* r) {
        if (!r) return 0;
        int lbs = branch_size(r->lchild);
        int rbs = branch_size(r->rchild);
        return lbs + rbs + (r->lchild && r->rchild);
    }

    /**
     * 152-06
     */
    void swap_lr() {
        swap_lr(root);
    }

    static void swap_lr(Node<T>* r) {
        if (!r) return;
        std::swap(r->lchild, r->rchild);
        swap_lr(r->lchild);
        swap_lr(r->rchild);
    }

    /**
     * 152-07
     */
    int pre_ord_kth(int k) const {
        T kth = INT_MAX;
        pre_ord_kth(root, k - 1, 0, kth);
        return kth;
    }

    static void pre_ord_kth(Node<T>* r, int k, int pos, T& kth) {
        if (!r) return;
        if (pos == k) {
            kth = r->data;
            return;
        }
        pre_ord_kth(r->lchild, k, ++pos, kth);
        pre_ord_kth(r->rchild, k, ++pos, kth);
    }

    /**
     * 152-08
     */
    void remove(const T& x) {
        remove(&root, x);
    }

    static void remove(Node<T>** r, const T& x) {
        if (!*r) return;
        if ((*r)->data == x) {
            delete_subtree(*r);
            *r = nullptr;
            return;
        }
        remove(&(*r)->lchild, x);
        remove(&(*r)->rchild, x);
    }

    static void delete_subtree(Node<T>* r) {
        if (!r) return;
        delete_subtree(r->lchild);
        delete_subtree(r->rchild);
        delete r;
    }

    /**
     * 152-09
     * 先序遍历，使用哈希表维护路径
     */
    void find_ancestors(const T& x) {
        if (!root) return;

        std::stack<Node<T>*> s;
        std::unordered_map<Node<T>*, Node<T>*> fa;
        s.push(root);
        fa[root] = nullptr;
        Node<T>* target = nullptr;
        while (!s.empty()) {
            Node<T>* cur = s.top();
            s.pop();
            if (cur->data == x) {
                target = cur;
                break;
            }
            if (cur->lchild) {
                fa[cur->lchild] = cur;
                s.push(cur->lchild);
            }
            if (cur->rchild) {
                fa[cur->rchild] = cur;
                s.push(cur->rchild);
            }
        }

        std::vector<T> ans;
        Node<T>* p = fa[target];
        while (p) {
            ans.push_back(p->data);
            p = fa[p];
        }

        for (const auto& it : ans) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }

    // 递归版：后序遍历，回溯时打印父节点
    void find_ancestors_r(const T& x) {
        find_ancestors_r(root, x);
        std::cout << std::endl;
    }

    static bool find_ancestors_r(Node<T>* r, const T& x) {
        if (!r) return false;
        if (r->data == x) return true;
        if (find_ancestors_r(r->lchild, x) || find_ancestors_r(r->rchild, x)) {
            std::cout << r->data << ' ';
            return true;
        }
        return false;
    }

    /**
     * 152-10
     * 非递归
     */
    Node<T>* lca(Node<T>* p, Node<T>* q) {
        std::unordered_map<Node<T>*, Node<T>*> fa;
        std::stack<Node<T>*> s;
        fa[root] = nullptr;
        s.push(root);

        // 先序遍历，搞出fa
        while (!fa.count(p) || !fa.count(q)) {
            Node<T>* cur = s.top();
            s.pop();
            if (cur->lchild) {
                fa[cur->lchild] = cur;
                s.push(cur->lchild);
            }
            if (cur->rchild) {
                fa[cur->rchild] = cur;
                s.push(cur->rchild);
            }
        }

        // 搞出p的祖先链
        std::unordered_set<Node<T>*> ancestors;
        while (p) {
            ancestors.insert(p);
            p = fa[p];
        }

        // q上跳，直到跳到p的祖先链中
        while (!ancestors.count(q)) {
            q = fa[q];
        }

        return q;
    }

    // 递归版
    Node<T>* lca_r(Node<T>* p, Node<T>* q) {
        return lca_r(root, p, q);
    }

    static Node<T>* lca_r(Node<T>* r, Node<T>* p, Node<T>* q) {
        if (!r || r == p || r == q) return r;
        Node<T>* left = lca_r(r->lchild, p, q);
        Node<T>* right = lca_r(r->rchild, p, q);
        if (left && right) return r; // p q 分属左右子树
        return left ? left : right;  // p q 在同一边
    }

    /**
     * 152-11
     */
    int width() const {
        std::queue<Node<T>*> q;
        q.push(root);
        int max_width = 0, width = 0;
        while (!q.empty()) {
            width = q.size();
            max_width = std::max(max_width, width);
            for (int i = 0; i < width; ++i) {
                auto* cur = q.front();
                q.pop();
                if (cur->lchild) q.push(cur->lchild);
                if (cur->rchild) q.push(cur->rchild);
            }
        }
        return max_width;
    }

    // 递归版本
    int width_r() const {
        std::map<int, int> mp; // k-深度 v-节点数
        width_r(root, 0, mp);
        if (mp.empty()) return 0;
        int max_width = 0;
        for (const auto& [dep, cnt] : mp) {
            max_width = std::max(max_width, cnt);
        }
        return max_width;
    }

    static void width_r(Node<T>* r, int dep, std::map<int, int>& mp) {
        if (!r) return;

        mp[dep]++;
        width_r(r->lchild, dep + 1, mp);
        width_r(r->rchild, dep + 1, mp);
    }

    /**
     * 153-13
     */
    Node<T>* link_leaves_r() {
        Node<T>*head = nullptr, *pre = nullptr;
        link_leaves_r(root, head, pre);
        return head;
    }

    // 递归版本，中序遍历
    static void link_leaves_r(Node<T>* r, Node<T>*& head, Node<T>*& pre) {
        if (!r) return;
        link_leaves_r(r->lchild, head, pre);
        if (!r->lchild && !r->rchild) {
            if (!pre) {
                head = r;
                pre = r;
            } else {
                pre->rchild = r;
                pre = r;
            }
        }
        link_leaves_r(r->rchild, head, pre);
        pre->rchild = nullptr;
    }

    /**
     * 153-15
     */
    int wpl_r() const {
        return wpl_r(root, 0);
    }

    static int wpl_r(Node<T>* r, int d) {
        if (!r) return 0;
        if (!r->lchild && !r->rchild) return r->data * d;
        return wpl_r(r->lchild, d + 1) + wpl_r(r->rchild, d + 1);
    }

    /**
     * 153-16
     */
    std::string expr2in_r() const {
        return expr2in_r(root, true);
    }

    static std::string expr2in_r(Node<T>* r, bool is_root) {
        if (!r) return "";
        if (!r->lchild && !r->rchild) return std::string(1, r->data);
        std::stringstream stream;
        if (!is_root) stream << '(';
        stream << expr2in_r(r->lchild, false) << r->data << expr2in_r(r->rchild, false);
        if (!is_root) stream << ')';
        return stream.str();
    }

    /**
     * 177-05
     */
    int tree_deep_r() const {
        return tree_deep_r(root);
    }

    static int tree_deep_r(Node<T>* r) {
        if(!r) return 0;
        return std::max(tree_deep_r(r->lchild) + 1, tree_deep_r(r->rchild));
    }
};

/**
 * 152-12
 */
static void pre2post(const std::string& pre, std::string& post, int l, int r) {
    if (l > r) return;
    int len = (r - l + 1) >> 1;
    pre2post(pre, post, l + 1, l + len);
    pre2post(pre, post, l + len + 1, r);
    post += pre[l];
}

std::string pre2post(const std::string& pre) {
    std::string post;
    pre2post(pre, post, 0, pre.length() - 1);
    return post;
}

/**
 * 153-14
 */
template <typename T>
bool is_same(Node<T>* a, Node<T>* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return is_same(a->lchild, b->rchild) && is_same(a->rchild, b->rchild);
}

/**
 * 153-17
 */
bool is_bst(const std::vector<int>& t) {
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == -1) continue;
        if (i * 2 + 1 >= t.size()) continue;
        int l = t[i * 2 + 1];
        if (i * 2 + 2 >= t.size()) {
            if (l > t[i]) {
                return false;
            }
            continue;
        }

        int r = t[i * 2 + 2];
        if (l == -1) {
            if (t[i] > r) {
                return false;
            }
        } else if (r == -1) {
            if (l > t[i]) {
                return false;
            }
        } else {
            if (l > t[i] || t[i] > r) {
                return false;
            }
        }
    }
    return true;
}

auto test_height = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1, new Node<int>{2}, new Node<int>{3}};

    // When
    int h = t.height();
    int h2 = t.height_r();

    // Then
    assert(h == 2);
    assert(h == 2);
};

auto test_is_complete = []() {
    // Given
    BiTree<int> t, t2;
    t.root = new Node<int>{1, new Node<int>{2}, new Node<int>{3}};
    t2.root = new Node<int>{1, new Node<int>{2, new Node<int>{3}}};

    // When
    bool res = t.is_complete();
    bool res2 = t2.is_complete();

    // Then
    assert(res == true);
    assert(res2 == false);
};

auto test_branch_size = []() {
    // Given
    BiTree<int> t, t2;
    t.root = new Node<int>{1, new Node<int>{2}, new Node<int>{3}};
    t2.root = new Node<int>{1, new Node<int>{2, new Node<int>{3}}};

    // When
    int bs = t.branch_size();
    int bs2 = t2.branch_size();

    // Then
    assert(bs == 1);
    assert(bs2 == 0);
};

auto test_swap_lr = []() {
    // Given
    BiTree<int> t, t2;
    t.root = new Node<int>{1, new Node<int>{2}, new Node<int>{3}};
    t2.root = new Node<int>{1, new Node<int>{2, new Node<int>{3}}};

    // When
    t.swap_lr();
    t2.swap_lr();

    // Then
    assert(t.root->lchild->data == 3);
    assert(t.root->rchild->data == 2);

    assert(t2.root->lchild == nullptr);
    assert(t2.root->rchild->data == 2);
    assert(t2.root->rchild->lchild == nullptr);
    assert(t2.root->rchild->rchild->data == 3);
};

auto test_pre_ord_kth = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1, new Node<int>{2}, new Node<int>{3}};

    // When
    int res = t.pre_ord_kth(1);
    int res2 = t.pre_ord_kth(2);
    int res3 = t.pre_ord_kth(3);

    // Then
    assert(res == 1);
    assert(res2 == 2);
    assert(res3 == 3);
};

auto test_remove = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1, new Node<int>{2, new Node<int>{3}}, new Node<int>{4}};

    // When
    t.remove(2);

    // Then
    assert(t.root != nullptr);
    assert(t.root->lchild == nullptr);
    assert(t.root->rchild != nullptr);
};

auto test_print_fa = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1, new Node<int>{2, new Node<int>{3}}, new Node<int>{4}};

    // When
    t.find_ancestors(3);
    t.find_ancestors(4);

    t.find_ancestors_r(3); // (3) 2 1
    t.find_ancestors_r(4); // (4) 1
};

auto test_lca = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1};
    t.root->lchild = new Node<int>{2, nullptr, new Node<int>{5}};
    t.root->rchild = new Node<int>{3};
    Node<int>* p = t.root->lchild->lchild = new Node<int>{4};
    Node<int>* q = t.root->rchild->rchild = new Node<int>{6};

    // When
    auto* res = t.lca_r(p, q);
    auto* res2 = t.lca(p, q);

    // Then
    assert(res->data == 1);
    assert(res2->data == 1);
};

auto test_width = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1};
    t.root->lchild = new Node<int>{2, new Node<int>{4}, new Node<int>{5}};
    t.root->rchild = new Node<int>{3, nullptr, new Node<int>{6}};

    // When
    int res = t.width();
    int res2 = t.width_r();

    // Then
    assert(res == 3);
    assert(res2 == 3);
};

auto test_pre2post = []() {
    // Given
    std::string pre = "1245367"; // 满二叉树

    // When
    auto res = pre2post(pre);

    // Then
    assert(res == "4526731");
};

auto test_link_leaves = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1};
    t.root->lchild = new Node<int>{2, new Node<int>{4}, new Node<int>{5}};
    t.root->rchild = new Node<int>{3, nullptr, new Node<int>{6}};

    // When
    auto* head = t.link_leaves_r();

    // Then
    for (Node<int>* p = head; p; p = p->rchild) {
        std::cout << p->data << ' '; // 4 5 6
    }
    std::cout << std::endl;

    // Finally
    t.root->lchild->lchild->rchild = nullptr;
    t.root->lchild->rchild->rchild = nullptr;
};

auto test_is_same = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1};
    t.root->lchild = new Node<int>{2, new Node<int>{4}, new Node<int>{5}};
    t.root->rchild = new Node<int>{3, nullptr, new Node<int>{6}};

    BiTree<int> t2;
    t2.root = new Node<int>{1};
    t2.root->lchild = new Node<int>{2, new Node<int>{4}, new Node<int>{5}};
    t2.root->rchild = new Node<int>{3, nullptr, new Node<int>{6}};

    // When
    bool res = is_same(t.root, t2.root);

    // Then
    assert(res == true);
};

auto test_wpl = []() {
    // Given
    BiTree<int> t;
    t.root = new Node<int>{1};
    t.root->lchild = new Node<int>{2, new Node<int>{4}, new Node<int>{5}};
    t.root->rchild = new Node<int>{3, nullptr, new Node<int>{6}};

    // When
    auto res = t.wpl_r();

    // Then
    assert(res == 30);
};

auto test_expr2in = []() {
    // Given
    BiTree<char> t;
    t.root = new Node<char>(
        '*',
        new Node<char>(
            '+',
            new Node<char>('a'),
            new Node<char>('b')),
        new Node<char>(
            '*',
            new Node<char>('c'),
            new Node<char>(
                '-',
                nullptr,
                new Node<char>('d'))));

    BiTree<char> t2;
    t2.root = new Node<char>(
        '+',
        new Node<char>(
            '*',
            new Node<char>('a'),
            new Node<char>('b')),
        new Node<char>(
            '-',
            nullptr,
            new Node<char>(
                '-',
                new Node<char>('c'),
                new Node<char>('d'))));

    // When
    auto res = t.expr2in_r();
    auto res2 = t2.expr2in_r();

    // Then
    std::cout << res << std::endl;
    std::cout << res2 << std::endl;
};

auto test_is_bst = []() {
    // Given
    std::vector<int> t = {40, 25, 60, -1, 30, -1, 80, -1, -1, 27};
    std::vector<int> t2 = {40, 50, 60, -1, 30, -1, -1, -1, -1, -1, 35};

    // When
    bool res = is_bst(t);
    bool res2 = is_bst(t2);

    // Then
    assert(res == true);
    assert(res2 == false);
};

auto test_tree_deep = []() {
    // Given
    BiTree<char> t;
    t.root = new Node<char>(
        'G',
        new Node<char>(
            'H',
            new Node<char>(
                'K',
                nullptr,
                new Node<char>('L')
            ),
            new Node<char>(
                'I',
                nullptr,
                new Node<char>(
                    'J',
                    new Node<char>(
                        'M',
                        new Node<char>('P'),
                        new Node<char>(
                            'N',
                            nullptr,
                            new Node<char>('O')
                        )
                    )
                )
            ) 
        )
    );

    // When
    auto res = t.tree_deep_r();

    // Then
    assert(res == 4);
};

int main() {
    test_height();
    test_is_complete();
    test_branch_size();
    test_swap_lr();
    test_pre_ord_kth();
    test_remove();
    test_print_fa();
    test_lca();
    test_width();
    test_pre2post();
    test_link_leaves();
    // test_is_same(); // WA
    test_wpl();
    test_expr2in();
    test_is_bst();
    test_tree_deep();
}