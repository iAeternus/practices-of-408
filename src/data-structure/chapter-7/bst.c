#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 二叉排序树节点
typedef struct _AVLNode {
    int val;
    struct _AVLNode* lch;
    struct _AVLNode* rch;
    struct _AVLNode* fa;
} BSTNode;

BSTNode* make_node(int val, BSTNode* lch, BSTNode* rch, BSTNode* fa) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    assert(node != NULL);
    node->val = val;
    node->lch = lch;
    node->rch = rch;
    node->fa = fa;
}

// 二叉排序树
typedef struct AVLTree {
    int siz;
    BSTNode* root;
} BST;

void bst_create(BST* t) {
    t->siz = 0;
    t->root = NULL;
}

static void clear(BSTNode* node) {
    if (!node) return;
    clear(node->lch);
    clear(node->rch);
    free(node);
}

void bst_destroy(BST* t) {
    if (!t) return;
    clear(t->root);
}

BSTNode* bst_find(const BST* t, int val) {
    if (!t) return NULL;
    BSTNode* p = t->root;
    while (p) {
        if (val < p->val) {
            p = p->lch;
        } else if (val > p->val) {
            p = p->rch;
        } else {
            return p;
        }
    }
    return NULL;
}

bool bst_insert(BST* t, int val) {
    if (!t) return false;

    // 空树
    if (!t->root) {
        t->root = make_node(val, NULL, NULL, NULL);
        t->siz++;
        return true;
    }

    BSTNode *p = t->root, *fa = NULL;
    while (p) {
        fa = p;
        if (val < p->val) {
            p = p->lch;
        } else if (val > p->val) {
            p = p->rch;
        } else {
            return false; // 重复
        }
    }

    BSTNode* new_node = make_node(val, NULL, NULL, fa);
    if (val < fa->val) {
        fa->lch = new_node;
    } else {
        fa->rch = new_node;
    }
    t->siz++;
    return true;
}

static BSTNode* find_min(BSTNode* node) {
    if (!node) return NULL;
    while (node->lch) {
        node = node->lch;
    }
    return node;
}

void bst_remove(BST* t, int val) {
    if (!t || !t->root) return;

    BSTNode* p = bst_find(t, val); // p指向待删除节点
    if (!p) return;

    // 有左右子树
    if (p->lch && p->rch) {
        BSTNode* succ = find_min(p->rch); // 右子树中序第一个孩子就是右子树的最小值
        p->val = succ->val;               // 用后继结点的值覆盖当前节点
        p = succ;                         // 转换为删除后继结点
    }

    BSTNode* child = p->lch ? p->lch : p->rch;
    BSTNode* fa = p->fa;

    // 更新父节点
    if (fa) {
        if (fa->lch == p) {
            fa->lch = child;
        } else {
            fa->rch = child;
        }
    } else {
        t->root = child; // 根节点
    }

    // 更新子节点
    if (child) {
        child->fa = fa;
    }

    free(p);
    t->siz--;
}

static void print_inorder(const BSTNode* node) {
    if (!node) return;
    print_inorder(node->lch);
    printf("%d ", node->val);
    print_inorder(node->rch);
}

void test_bst() {
    BST t;
    bst_create(&t);

    // insert
    bst_insert(&t, 50);
    bst_insert(&t, 30);
    bst_insert(&t, 70);
    bst_insert(&t, 20);
    bst_insert(&t, 40);
    bst_insert(&t, 60);
    bst_insert(&t, 80);

    print_inorder(t.root); // 20 30 40 50 60 70 80
    putchar('\n');

    // find
    BSTNode* f = bst_find(&t, 40);
    assert(f != NULL);
    assert(f->val == 40);

    // remove
    bst_remove(&t, 20);
    print_inorder(t.root); // 30 40 50 60 70 80
    putchar('\n');

    bst_remove(&t, 30);    // 只有一个子节点
    print_inorder(t.root); // 40 50 60 70 80
    putchar('\n');

    bst_remove(&t, 50);    // 有两个子节点
    print_inorder(t.root); // 40 60 70 80
    putchar('\n');

    assert(t.siz == 4);

    bst_destroy(&t);
}

int main() {
    test_bst();
    return 0;
}