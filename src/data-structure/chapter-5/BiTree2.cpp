#include <bits/stdc++.h>

const int N = 1e3 + 5;

template <typename T>
struct Node {
    T data;
    Node<T>* lchild = nullptr;
    Node<T>* rchild = nullptr;

    Node(const T& data, Node<T>* lchild = nullptr, Node<T>* rchild = nullptr) :
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
};

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

int main() {
    test_height();
    test_is_complete();
    test_branch_size();
    test_swap_lr();
    test_pre_ord_kth();
    test_remove();
    test_print_fa();
    test_lca();
}